#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h>

// Define data types for the language
typedef enum {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_ERROR
} DataType;

// Symbol structure for variables
typedef struct Symbol {
    char* name;
    DataType type;
    union {
        int int_val;
        bool bool_val;
    } value;
    struct Symbol* next;
} Symbol;

// Symbol table structure
typedef struct {
    Symbol* head;
    Symbol* tail;
} SymbolTable;

// Function declarations
void init_symbol_table(void);
Symbol* create_symbol(char* name, DataType type);
Symbol* lookup_symbol(char* name);
void add_symbol(Symbol* symbol);
void print_symbol_table(void);
void free_symbol_table(void);

#endif 