# Compiler Demo

This document demonstrates the compiler's capabilities with example programs.

## Quick Start

```bash
# Build the compiler
mingw32-make

# Run with a test program
compiler.exe < inputs/valid/control_flow.txt
```

## Example 1: Control Flow and Arithmetic

**Input Program** (`inputs/valid/control_flow.txt`):
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

**Expected Output**:
```
5
10
```

**Demonstrates**:
- Variable declarations with initialization
- If-else conditional branching
- While loops
- Comparison operators (`<`, `>=`)
- Arithmetic operations (`+`)
- Boolean logic

## Example 2: Comprehensive Operations

**Input Program** (`inputs/valid/operations_test.txt`):
```c
// Arithmetic Operations
int a = 15;
int b = 3;
int result;

result = a + b;
print result;      // Prints 18

result = a - b;
print result;      // Prints 12

result = a * b;
print result;      // Prints 45

result = a / b;
print result;      // Prints 5

// Boolean Operations
bool test = true;
bool other = false;
bool final;

final = test && other;
print final;            // Prints false

final = test || other;
print final;            // Prints true
```

**Expected Output**:
```
18
12
45
5
false
true
```

**Demonstrates**:
- All arithmetic operators (`+`, `-`, `*`, `/`)
- Boolean operators (`&&`, `||`)
- Variable reassignment
- Comment support

## Error Handling Examples

### Type Mismatch Error

**Input**:
```c
int x = 5;
bool y = x;  // Error!
```

**Output**:
```
Error at line 2: Cannot initialize 'y' (bool) with value of type int
```

### Undefined Variable Error

**Input**:
```c
int a = 5;
b = 10;  // Error - b not declared
```

**Output**:
```
Error at line 2: Undefined variable 'b'
```

### Division by Zero Error

**Input**:
```c
int x = 5;
int y = 0;
int result = x / y;  // Error!
```

**Output**:
```
Error at line 3: Division by zero
```

## Type System Features

The compiler enforces strict static typing:

```c
// Valid: Same types
int a = 5 + 3;
bool b = true && false;
bool c = (10 > 5);

//Invalid: Type mismatches
int x = 5 + true;        // Error: Cannot add int and bool
bool y = 10 && 5;        // Error: AND requires boolean operands
int z = true;            // Error: Cannot assign bool to int
```

## Language Features Summary

### Supported
- **Data Types**: `int`, `bool`
- **Operators**: `+`, `-`, `*`, `/`, `&&`, `||`, `!`, `<`, `>`, `<=`, `>=`, `==`, `!=`
- **Control Flow**: `if`, `if-else`, `while`
- **I/O**: `print`
- **Comments**: `// single-line comments`

### Not Supported (By Design)
- Functions
- Arrays
- Pointers
- Structs
- Multiple scopes
- Type casting
