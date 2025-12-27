#include <stdio.h>
#include <dlfcn.h>
#include <chrono>

// Global timestamp initialized once
static long long g_timestamp = std::chrono::duration_cast<std::chrono::seconds>(
    std::chrono::system_clock::now().time_since_epoch()
).count();

// Library API - exported functions with C linkage
extern "C" {
    __attribute__((visibility("default"))) long long dyexe_get_time(void) {
        return g_timestamp;
    }
}

// Executable entry point
int main(int argc, char *argv[]) {
    printf("Running as executable!\n");
    printf("Timestamp: %lld\n", dyexe_get_time());

    if (argc > 1) {
        printf("\nArguments received:\n");
        for (int i = 1; i < argc; i++) {
            printf("  arg[%d]: %s\n", i, argv[i]);
        }
    }

    return 0;
}
