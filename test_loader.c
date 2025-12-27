#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

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

    // Call the loaded function
    printf("Calling library function:\n");
    printf("Timestamp from library: %lld\n", time_func());

    // Close the library
    dlclose(handle);
    printf("\nLibrary closed successfully.\n");

    return 0;
}
