# Basic C Compiler

A simple compiler for a C-like language that supports basic arithmetic operations, control structures, and static type checking. The compiler supports integer and boolean types, with strict type checking and detailed error reporting.

## Features

- Integer and boolean data types
- Basic arithmetic operations (+, -, *, /)
- Logical operations (and, or, not)
- Comparison operations (>, <, >=, <=, ==, !=)
- Control structures (if-else, while)
- Print and return statements
- Static type checking
- Error reporting with line numbers

## Building

### Prerequisites

#### For Unix/Linux/MacOS:
```bash
# For Ubuntu:
sudo apt-get update
sudo apt-get install flex bison gcc make

# For MacOS with Homebrew:
brew install flex bison gcc make
```

#### For Windows:
1. Install MinGW (GCC)
2. Install Flex and Bison
3. Add both to your PATH

### Build Commands

```bash
# Using make
make clean
make

# Manual build
flex lexer.l
bison -d parser.y
gcc lex.yy.c parser.tab.c symbol_table.c operations.c -o compiler
```

## Running

```bash
# Interactive mode
./compiler

# With input file
./compiler < input_file.txt
```

## Example Program

```c
int x = 5;
int y = 10;
bool flag = true;

if (x < y) {
    print x;    // Will print 5
} else {
    print y;
}

while (flag) {
    x = x + 1;
    if (x >= 10) {
        flag = false;
    }
}

print x;    // Will print 10
```

## Notes
- All variables must be declared and initialized
- Supports negative numbers and type checking
- Only supports single scope (no nested scopes)
- Type mismatches and other errors are reported with line numbers