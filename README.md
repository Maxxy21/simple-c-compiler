# Basic C Compiler

This compiler implements a subset of the C programming language focusing on fundamental operations and type checking. It parses and evaluates statements written in a C-like syntax, supporting basic data types (int and bool), arithmetic operations, and control structures.

## Features

### Core Features:

- Basic data types (int, bool)
- Variable declarations and assignments
- Arithmetic operations (+, -, *, /)
- Logical operations (and, or, not)
- Comparison operations (>, <, >=, <=, ==, !=)
- Control structures (if-else, while)
- Print and return statements

### Type System:

- Static type checking
- Type verification for operations
- Error reporting with line numbers

## Grammar

```bnf
program -> statement_list | ε

statement_list -> statement
                | statement_list statement

statement -> declaration ;
           | assignment ;
           | if_statement
           | while_statement
           | print_statement ;
           | return_statement ;

declaration -> type_specifier IDENTIFIER
             | type_specifier IDENTIFIER = expression

type_specifier -> int | bool

assignment -> IDENTIFIER = expression

if_statement -> IF ( expression ) { statement_list }
              | IF ( expression ) { statement_list } ELSE { statement_list }

while_statement -> WHILE ( expression ) { statement_list }
```

## Example Programs

### Valid Programs

#### 1. Control Structures (inputs/valid/control_flow.txt)

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
This example demonstrates:
- Variable initialization
- If-else statements
- While loops
- Boolean conditions
- Arithmetic operations

#### 2. Operations Test (inputs/valid/operations_test.txt)

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
This example shows:
- All arithmetic operations
- Logical operations
- Mixed declarations and assignments
- Print statements

### Invalid Programs

#### 1. Type Mismatch (inputs/invalid/type_mismatch.txt)
```c
int x = 5;
bool y = x;  // Error: Cannot initialize bool with int
```
Error: Type mismatch in initialization - Cannot assign integer value to boolean variable

#### 2. Undefined Variable (inputs/invalid/undefined_var.txt)
```c
int a = 5;
b = 10;  // Error: b not declared
```
Error: Variable 'b' has not been defined

#### 3. Invalid Operation (inputs/invalid/invalid_operation.txt)

```c
bool flag = true;
bool other = false;
bool result = flag + other;  // Error: Cannot add booleans
```

Error: Cannot perform addition between boolean operands

#### 4. Division by Zero (inputs/invalid/div_by_zero.txt)

```c
int x = 5;
int y = 0;
int result = x / y;  // Error: Division by zero
```

Error: Division by zero

#### 5. Variable Redeclaration (inputs/invalid/var_redeclaration.txt)

```c
int x = 5;
int x = 10;  // Error: x already declared
```

Error: Variable 'x' already declared

#### 6. Invalid Token (inputs/invalid/invalid_token.txt)
```c
gibberish  // Error: Unrecognized token
```
Error: Lexical error - Unrecognized character

### Directory Structure for input files
```
inputs/
├── valid/
│   ├── control_flow.txt
│   └── operations_test.txt
└── invalid/
    ├── type_mismatch.txt
    ├── undefined_var.txt
    ├── invalid_operation.txt
    ├── div_by_zero.txt
    ├── var_redeclaration.txt
    └── invalid_token.txt
```

## Valid Input Examples

```c
// Variable declarations and initialization
int x = 5;
bool flag = true;

// Control structures
if (x > 0) {
    print x;
} else {
    x = 0;
}

while (flag) {
    x = x + 1;
    if (x > 10) {
        flag = false;
    }
}
```

## Type Rules and Restrictions

### Type Rules:
- Arithmetic operations (+, -, *, /) only work with integers
- Logical operations (and, or, not) only work with booleans
- Comparison operations return boolean values
- Variables must be declared before use

### Invalid Operations:
```c
x = 5 + true;              // Cannot mix int and bool
bool result = 5 or 5;      // Logical operations need booleans
int res = true + true;     // Cannot add booleans
print (12 and true);       // Invalid types for AND
```

## Building and Running

### Prerequisites

#### For Unix/Linux/MacOS:
1. Install the required tools using your package manager:
   ```bash
   # For Ubuntu:
   sudo apt-get update
   sudo apt-get install flex bison gcc make

   # For MacOS with Homebrew:
   brew install flex bison gcc make
   ```

#### For Windows:
1. Install GCC (MinGW):
   - Download MinGW installer from https://sourceforge.net/projects/mingw/
   - Add `C:\MinGW\bin` to your PATH

2. Install Flex and Bison:
   - Download from https://gnuwin32.sourceforge.net/packages/flex.htm
   - Download from https://gnuwin32.sourceforge.net/packages/bison.htm
   - Install both packages
   - Add `C:\GnuWin32\bin` to your PATH

### Build Commands

#### For Unix/Linux/MacOS:
```bash
# Using make
make clean
make

# Manual build
flex lexer.l
bison -d parser.y
gcc lex.yy.c parser.tab.c symbol_table.c operations.c -o compiler
```

#### For Windows:
```bash
# Using make
mingw32-make clean
mingw32-make

# Manual build
flex lexer.l
bison -d parser.y
gcc lex.yy.c parser.tab.c symbol_table.c operations.c -o compiler.exe
```

### Running the Compiler

#### For Unix/Linux/MacOS:
```bash
# Interactive mode
./compiler

# With input file
./compiler < input_file.txt
```

#### For Windows:
```bash
# Interactive mode
compiler.exe

# With input file
compiler.exe < input_file.txt
```


### Common Error Messages:
- "Variable already declared" - Attempting to redeclare a variable
- "Undefined variable" - Using a variable before declaration
- "Type mismatch" - Invalid type in operation or assignment
- "Division by zero" - Attempting to divide by zero

## Implementation Details

### Components:
1. Lexical Analyzer (lexer.l)
    - Tokenizes input
    - Handles comments and whitespace

2. Parser (parser.y)
    - Implements grammar rules
    - Performs type checking
    - Handles error reporting

3. Symbol Table
    - Dynamic linked list implementation
    - Stores variable information
    - Supports lookup and insertion

4. Operations
    - Type-checked arithmetic operations
    - Logical operations
    - Comparison operations

## Limitations
- No function declarations/calls
- No arrays or pointers
- Limited to int and bool types
- Single scope (no nested scopes)
- Control structures are parsed but execution flow is not fully implemented