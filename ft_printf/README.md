# ft_printf

A custom implementation of the `printf` function in C, created as part of the 42 curriculum.

## Overview

`ft_printf` replicates the behavior of the standard `printf` function. It provides formatted output based on specific format specifiers, processing variable arguments with `va_list`.

### Supported Specifiers:
- **`%c`**: Print a single character
- **`%s`**: Print a string
- **`%p`**: Print a memory address (pointer)
- **`%d` / `%i`**: Print a signed integer
- **`%u`**: Print an unsigned integer
- **`%x` / `%X`**: Print a hexadecimal number (lowercase/uppercase)
- **`%%`**: Print a literal percent sign

## File Structure

- **`ft_printf.c`**: Main implementation of the `ft_printf` function.
- **`ft_printf.h`**: Header file with function prototypes and necessary includes.
- **Utility Functions**:
  - `print_char.c`: Handles `%c`.
  - `print_string.c`: Handles `%s`.
  - `print_pointer.c`: Handles `%p`.
  - `print_number.c`: Handles `%d` and `%i`.
  - `print_unsigned_number.c`: Handles `%u`.
  - `print_hex.c`: Handles `%x` and `%X`.
- **Helper Functions**:
  - `ft_putchar_fd.c`
  - `ft_putstr_fd.c`
  - `ft_strlen.c`

## Compilation and Usage

### Compilation
Use the provided `Makefile` to compile the project:
```bash
make
```

This will generate an object file and an executable.

### Usage

To use the `ft_printf` function in your project:

1.  Include `ft_printf.h` in your source file.
2.  Call `ft_printf` as you would use the standard `printf`.

Example:
```
#include "ft_printf.h"

int main()
{
    ft_printf("Hello, World! My number is %d and my hex is %x\n", 42, 42);\
    return 0;
}
```
