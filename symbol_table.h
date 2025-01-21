#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h>

// Data types
typedef enum {
    TYPE_INT,    // Integer values
    TYPE_BOOL,   // Boolean values (true/false)
    TYPE_ERROR   // Used for error handling
} DataType;

// Represents a single variable/symbol in our compiler
// Stores the name, type, and value of the variable
typedef struct Symbol {
    char* name;              // Variable name/identifier
    DataType type;           // Variable type (int/bool)
    union {
        int int_val;         // Value if type is int
        bool bool_val;       // Value if type is bool
    } value;
    struct Symbol* next;     // Points to next symbol in list
} Symbol;

// Contains all variables/symbols in our program
// Implemented as a linked list for dynamic storage
typedef struct {
    Symbol* head;    // First symbol in the list
    Symbol* tail;    // Last symbol in the list
} SymbolTable;

// Function declarations
void init_symbol_table(void);
Symbol* create_symbol(char* name, DataType type);
Symbol* lookup_symbol(char* name);
void add_symbol(Symbol* symbol);
void print_symbol_table(void);
void free_symbol_table(void);

#endif