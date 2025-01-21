# Compiler Project Report

## 1. Project Overview

### 1.1 Introduction
This project implements a compiler for a subset of the C programming language, focusing on fundamental operations and type checking. The compiler supports basic data types (int and bool), control structures, and arithmetic/logical operations while enforcing strong type safety.

### 1.2 Key Features
- Static type checking system
- Integer and Boolean data types
- Arithmetic and logical operations
- Control structures (if-else, while)
- Variable declarations and assignments
- Print statements
- Error reporting with line numbers

## 2. Technical Implementation

### 2.1 Components

#### 2.1.1 Lexical Analyzer (lexer.l)
- Implemented using Flex
- Recognizes tokens: keywords, operators, identifiers, literals
- Handles comments and whitespace
- Tracks line numbers for error reporting
- Patterns defined for integers, identifiers, and operators

#### 2.1.2 Parser (parser.y)
- Implemented using Bison
- Defines grammar rules for the language
- Performs type checking
- Manages symbol table operations
- Handles error detection and reporting

#### 2.1.3 Symbol Table (symbol_table.h/c)
- Dynamic linked list implementation
- Stores variable information
- Supports variable lookup and insertion
- Tracks variable types and values
- Prevents duplicate declarations

#### 2.1.4 Operations (operations.h/c)
- Implements arithmetic operations
- Handles logical operations
- Performs type checking for operations
- Creates temporary results

### 2.2 Type System
The compiler implements a strong type system with:
- Integer type (int)
- Boolean type (bool)
- No implicit type conversions
- Type checking for operations
- Type compatibility verification

### 2.3 Error Handling
The compiler provides comprehensive error detection for:
- Undefined variables
- Type mismatches
- Invalid operations
- Division by zero
- Duplicate variable declarations
- Invalid tokens
- Syntax errors

## 3. Language Features

### 3.1 Supported Operations
- Arithmetic: +, -, *, /
- Comparison: <, >, <=, >=, ==, !=
- Logical: AND, OR, NOT
- Assignment: =

### 3.2 Control Structures
- If-else statements
- While loops
- Block statements

### 3.3 Input/Output
- Print statements for both types
- Proper formatting of output

## 4. Testing

### 4.1 Test Cases
The project includes various test cases:

#### Valid Programs:
- Control flow testing
- Operations testing
- Variable declarations
- Type checking
- Expression evaluation

#### Invalid Programs:
- Type mismatch detection
- Undefined variable usage
- Invalid operations
- Division by zero
- Variable redeclaration

### 4.2 Test Coverage
The test suite covers:
- Basic data types
- Variable operations
- Control structures
- Error handling
- Type checking
- Expression evaluation

## 5. Project Requirements Analysis

### 5.1 Required Components
- ✓ Lexical Analyzer with regular expressions
- ✓ Syntactic Productions using YACC
- ✓ Semantic Rules for type checking
- ✓ Symbol Table implementation

### 5.2 Additional Features
- Comprehensive error messages
- Line number tracking
- Dynamic symbol table
- Type safety enforcement

## 6. Compilation and Usage

### 6.1 Build Process
```bash
make clean
make
```

### 6.2 Running the Compiler
```bash
./compiler < input_file.txt
```

### 6.3 Platform Support
- Unix/Linux
- MacOS
- Windows (with MinGW)

## 7. Limitations and Future Improvements

### 7.1 Current Limitations
- Single scope (no nested scopes)
- No function declarations
- Limited to int and bool types
- No arrays or pointers

### 7.2 Potential Improvements
- Multiple scope support
- Function implementation
- Additional data types
- Array support
- Optimization passes
- Better error recovery

## 8. Conclusion
The compiler successfully implements a subset of C with strong type checking and error detection. It meets all core requirements while providing a solid foundation for future extensions. The modular design allows for easy addition of new features and optimizations.

## 9. Appendix

### 9.1 File Structure
```
project/
├── lexer.l
├── parser.y
├── symbol_table.h
├── symbol_table.c
├── operations.h
├── operations.c
├── README.md
└── inputs/
    ├── valid/
    └── invalid/
```

### 9.2 Sample Programs

Valid Program Example:
```c
int x = 5;
bool flag = true;
while (flag) {
    x = x + 1;
    if (x >= 10) {
        flag = false;
    }
}
print x;
```

Output:
```
10
```