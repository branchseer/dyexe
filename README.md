# dyexe - Dual-Purpose Executable/Library for macOS

This project demonstrates creating a macOS executable that can also be loaded as a dynamic library.

## How It Works

The binary is built as a Position Independent Executable (PIE) with exported symbols using C++:
- `-fPIC`: Position Independent Code
- `-Wl,-export_dynamic`: Export symbols for dynamic loading
- `-Wl,-pie`: Create a PIE executable
- `__attribute__((visibility("default")))`: Mark functions for export
- C++ std::chrono for timestamp initialization

## Building

```bash
make
```

This creates binaries in the `build/` directory:
- `build/dyexe` - The dual-purpose binary
- `build/test_loader` - A test program that loads dyexe as a library

## Usage

### As an Executable

The executable prints a Unix timestamp (seconds since epoch) to stdout:

```bash
build/dyexe
# Output: 1766845603
```

### As a Dynamic Library

```bash
build/test_loader build/dyexe
```

Or programmatically in C:

```c
void *handle = dlopen("./dyexe", RTLD_LAZY);
long long (*get_time)(void) = dlsym(handle, "dyexe_get_time");
long long timestamp = get_time();
dlclose(handle);
```

## Testing

Run all tests:

```bash
make test
```

This runs:
1. **Executable test** (`test_executable.sh`): Spawns the executable, captures stdout, and verifies the timestamp is close to current time
2. **Library test** (`test_loader`):
   - Loads dyexe as a dynamic library
   - Calls `dyexe_get_time()` twice and verifies both calls return the same value
   - Verifies the timestamp is close to current time

Run individual tests:

```bash
# Test executable mode
./test_executable.sh build/dyexe

# Test library mode
build/test_loader build/dyexe
```

## API Functions

- `long long dyexe_get_time(void)` - Returns Unix timestamp (seconds since epoch) initialized at program start

## Clean Up

```bash
make clean
```
