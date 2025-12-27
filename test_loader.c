#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[]) {
    const char *lib_path = argc > 1 ? argv[1] : "./dyexe";

    printf("Loading %s as dynamic library...\n\n", lib_path);

    // Open the executable as a dynamic library
    void *handle = dlopen(lib_path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        return 1;
    }

    // Clear any existing errors
    dlerror();

    // Load the dyexe_get_time function
    typedef long long (*dyexe_get_time_t)(void);
    dyexe_get_time_t time_func = (dyexe_get_time_t)dlsym(handle, "dyexe_get_time");

    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Error loading symbol 'dyexe_get_time': %s\n", error);
        dlclose(handle);
        return 1;
    }

    // Test 1: Call dyexe_get_time twice and verify it returns the same value
    printf("Test 1: Calling dyexe_get_time twice...\n");
    long long timestamp1 = time_func();
    long long timestamp2 = time_func();

    printf("  First call:  %lld\n", timestamp1);
    printf("  Second call: %lld\n", timestamp2);

    if (timestamp1 == timestamp2) {
        printf("  ✓ Both calls returned the same value\n\n");
    } else {
        fprintf(stderr, "  ✗ ERROR: Timestamps differ! Expected same value.\n");
        dlclose(handle);
        return 1;
    }

    // Test 2: Verify the timestamp is close to current time
    printf("Test 2: Verifying timestamp is close to current time...\n");
    time_t current_time = time(NULL);
    long long diff = llabs(current_time - timestamp1);

    printf("  Timestamp from library: %lld\n", timestamp1);
    printf("  Current time:           %lld\n", (long long)current_time);
    printf("  Difference:             %lld seconds\n", diff);

    // Allow up to 5 seconds difference (should be much less in practice)
    if (diff <= 5) {
        printf("  ✓ Timestamp is within acceptable range\n\n");
    } else {
        fprintf(stderr, "  ✗ ERROR: Timestamp differs by more than 5 seconds!\n");
        dlclose(handle);
        return 1;
    }

    // Close the library
    dlclose(handle);
    printf("All tests passed! Library closed successfully.\n");

    return 0;
}
