# MiniLibC

## Table of Contents

- [Overview](#overview)
- [Goals](#goals)
- [Features](#features)
  - [Required Functions](#required-functions)
  - [Bonus Functions](#bonus-functions)
- [Compilation & Usage](#compilation--usage)
- [Contributing](#contributing)
- [License](#license)

## Overview

MiniLibC is a minimalistic C-runtime library built from scratch in x86-64 NASM assembly. It allows you to replace—or override—standard libc functions via dynamic linking (`LD_PRELOAD`), offering insights into low-level implementations and performance characteristics.

## Goals

* **Educational**: Deepen understanding of common libc routines by reimplementing them in assembly.
* **Portable**: Produce a standalone dynamic ELF library (`libasm.so`) compatible with x86-64 Linux.
* **Lightweight**: Focus on clarity and minimal dependencies, avoiding any external C runtime requirements.

## Features

### Required Functions

* `strlen`
* `strchr`
* `strrchr`
* `memset`
* `memcpy`
* `strcmp`
* `memmove`
* `strncmp`
* `strcasecmp`
* `strstr`
* `strpbrk`
* `strcspn`

### Bonus Functions

* `All the library handle in 32 bits`
* `index` / `rindex`

*Feel free to extend with your own additional routines (e.g., `strtok`, `printf`), architectures (ARM, RISC-V), or other creative enhancements.*

## Compilation & Usage

1. **Clone the repository**

   ```bash
   git clone https://github.com/yourusername/minilibc.git
   cd minilibc
   ```
2. **Build**

   ```bash
   make        # Assemble all .asm files and link into libasm.so
   make re     # Rebuild from scratch (clean + build)
   make clean  # Remove object files and temporary artifacts
   make fclean # Remove everything including libasm.so
   ```
3. **Test / Run**
   Use `LD_PRELOAD` to override libc functions:

   ```bash
   LD_PRELOAD=$(pwd)/libasm.so ./your_program
   ```

## Contributing

Contributions, issues, and feature requests are welcome!

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/foo`).
3. Commit your changes (`git commit -am 'Add foo feature'`).
4. Push to the branch (`git push origin feature/foo`).
5. Open a Pull Request.

*Please stick to NASM syntax for new assembly routines and include tests where applicable.*

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.
