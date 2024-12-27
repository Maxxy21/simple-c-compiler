# Simple C Compiler Documentation

## 1. General Overview
This compiler implements a subset of the C programming language with support for basic data types, control structures, and arithmetic/logical operations. The compiler performs lexical analysis, syntax checking, and semantic analysis including type checking.

### Key Features:
- Integer and Boolean data types
- Variable declarations and assignments
- Control structures (if-else, while)
- Arithmetic and logical operations
- Print and return statements
- Type checking and error reporting

## 2. Grammar
The language follows this grammar:

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

expression -> simple_expression
            | expression AND simple_expression
            | expression OR simple_expression
```

## 3. Input Format Description

### Valid Input Examples:
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

// While loop
while (flag) {
    x = x + 1;
    if (x > 10) {
        flag = false;
    }
}
```

### Type Rules:
- Arithmetic operations (+, -, *, /) only work with integers
- Logical operations (and, or, not) only work with booleans
- Comparison operations return boolean values
- Variables must be declared before use
- Type mismatch in assignments will cause errors

## 4. Running Instructions

### Prerequisites:
- Flex
- Bison (YACC)
- GCC
- Make

### Building the Compiler:
1. Clone or download the source code
2. Navigate to the project directory
3. Run the following commands:
```bash
make clean  # Clean any previous builds
make        # Build the compiler
```

### Running the Compiler:
```bash
compiler.exe < ../test/valid-inputs/valid_input2.txt
```

### Common Error Messages:
- "Variable already declared" - Attempting to redeclare a variable
- "Undefined variable" - Using a variable before declaration
- "Type mismatch" - Invalid type in operation or assignment
- "Division by zero" - Attempting to divide by zero

## 5. Implementation Details

### Symbol Table:
- Implemented as a dynamic linked list
- Stores variable names, types, and values
- Supports lookup and insertion operations

### Type Checking:
- Static type checking during compilation
- Type verification for operations
- Error reporting with line numbers

### Error Handling:
- Syntax errors with line numbers
- Type mismatch errors
- Runtime error detection (e.g., division by zero)

## 6. Limitations
- No function declarations/calls
- No arrays or pointers
- Limited to int and bool types
- No string operations
- Single scope (no nested scopes)