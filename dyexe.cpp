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
    (void)argc;
    (void)argv;
    printf("%lld\n", dyexe_get_time());
    return 0;
}
