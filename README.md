# Lukakou - A hand-made compiler for a new language called Lukakou

## Description:

Lukakou is a project with the goal of developing a programming language and a compiler from scratch. The language is just a stupid one, with no real purpose, but it is a good way to learn about compilers and programming languages. This project aims to explore compilation mechanisms to assembly.

You can find more information about the Lukakou Language and to discover my journey in the development of this project in the [google doc](https://docs.google.com/document/d/1yH_NcJOKdF3nAJuB_L3KP5aXJXypyiT7SzUAfhG4d58/edit?usp=sharing). (It's in French for now, but I may translate it in English later).

## Features planned :

- Compilation to x86_64 assembly for UNIX systems.
- Common data types such as integers, characters, floating-point numbers, arrays, and strings.
- Iterative and conditional control structures: FOR, FOREACH, WHILE, DOWHILE, IF, ELSE, ELIF, IFNT.
- Definition and calling of functions.
- Entry point of the program with the "start" function.
- Support for standard input/output operations and UNIX system calls.

## Features implemented :
- None yet.

## Installation:

1. Clone the repository from GitHub: `https://github.com/LukasG62/Lukakou.git`
2. Navigate to the Lukakou directory
3. Compile the project using the provided Makefile: `make`

The project should compile without any errors. You can specify the compiler to use by setting the `CC` variable in the Makefile. By default, the Makefile uses `gcc`.
You can also clean the project by running `make clean`.

## Usage:

Once the project is compiled, you can use the Lukakou compiler to translate Lukakou source files into assembly code. Here's an example command:

```bash
./bin/lukac input.lkk
```
Make sure to read the google doc to understand the syntax of the Lukakou language. You can also find some examples in the `examples` directory.

Then you can use an assembler like `nasm` to assemble the generated assembly code into an executable file. Here's an example command:
```bash
nasm -f elf64 -o output.o output.asm
```
Finally, you can link the object file with a linker like `ld` to create an executable file. Here's an example command:
```bash
ld -o output output.o
```

## Requirements:

- UNIX-based operating system (Linux, macOS)
- C compiler compatible with C99
- Build tools (make, gcc, nasm, ld)
