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

This creates:
- `dyexe` - The dual-purpose binary
- `test_loader` - A test program that loads dyexe as a library

## Usage

### As an Executable

```bash
./dyexe [args...]
```

### As a Dynamic Library

```bash
./test_loader ./dyexe
```

Or programmatically in C:

```c
void *handle = dlopen("./dyexe", RTLD_LAZY);
long long (*get_time)(void) = dlsym(handle, "dyexe_get_time");
long long timestamp = get_time();
dlclose(handle);
```

## Testing

```bash
make test
```

## API Functions

- `long long dyexe_get_time(void)` - Returns Unix timestamp (seconds since epoch) initialized at program start

## Clean Up

```bash
make clean
```
