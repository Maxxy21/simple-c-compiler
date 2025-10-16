/**
 * @file symbol_table.c
 * @brief Symbol table implementation for variable storage and lookup
 *
 * Implements a linked-list based symbol table with separate tracking
 * for regular variables and temporary symbols used in expression evaluation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

extern int line_number;  // Current line number from lexer.l
static SymbolTable* table;  // Main symbol table for declared variables
static SymbolTable* temp_table;  // Track temporary symbols for cleanup

/**
 * Initializes both the main symbol table and temporary symbol table
 * Must be called before any symbol operations
 */
void init_symbol_table(void) {
    table = (SymbolTable*)malloc(sizeof(SymbolTable));
    table->head = NULL;
    table->tail = NULL;

    temp_table = (SymbolTable*)malloc(sizeof(SymbolTable));
    temp_table->head = NULL;
    temp_table->tail = NULL;
}

/**
 * Creates a new symbol with the given name and type
 * @param name The variable name (will be duplicated)
 * @param type The data type (TYPE_INT or TYPE_BOOL)
 * @return Pointer to newly allocated symbol with default value
 */
Symbol* create_symbol(char* name, DataType type) {
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->type = type;
    symbol->next = NULL;

    // Initialize default values
    if (type == TYPE_INT) {
        symbol->value.int_val = 0;
    } else if (type == TYPE_BOOL) {
        symbol->value.bool_val = false;
    }

    return symbol;
}

/**
 * Looks up a variable in the symbol table by name
 * @param name The variable name to search for
 * @return Pointer to symbol if found, NULL otherwise
 * @note Uses linear search O(n) - suitable for single-scope table
 */
Symbol* lookup_symbol(char* name) {
    Symbol* current = table->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * Adds a symbol to the main symbol table
 * @param symbol The symbol to add
 * @note Exits with error if variable name already exists (no redeclaration)
 */
void add_symbol(Symbol* symbol) {
    // Check if symbol already exists
    if (lookup_symbol(symbol->name) != NULL) {
        fprintf(stderr, "Error at line %d: Variable '%s' already declared\n",
                line_number, symbol->name);
        exit(1);
    }

    // Add to empty table
    if (table->head == NULL) {
        table->head = symbol;
        table->tail = symbol;
    }
    // Add to end of table
    else {
        table->tail->next = symbol;
        table->tail = symbol;
    }
}

void free_symbol_table(void) {
    Symbol* current = table->head;
    while (current != NULL) {
        Symbol* next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    free(table);
    table = NULL;
}

void print_symbol_table(void) {
    Symbol* current = table->head;
    printf("\nSymbol Table Contents:\n");
    printf("%-15s %-10s %-10s\n", "Name", "Type", "Value");
    printf("----------------------------------------\n");

    while (current != NULL) {
        printf("%-15s ", current->name);

        if (current->type == TYPE_INT) {
            printf("%-10s %d\n", "int", current->value.int_val);
        } else if (current->type == TYPE_BOOL) {
            printf("%-10s %s\n", "bool",
                   current->value.bool_val ? "true" : "false");
        }

        current = current->next;
    }
    printf("\n");
}

/**
 * Tracks a temporary symbol for later cleanup
 * @param temp The temporary symbol to track
 * @note Used by operations.c to track intermediate expression results
 */
void track_temp_symbol(Symbol* temp) {
    if (temp_table->head == NULL) {
        temp_table->head = temp;
        temp_table->tail = temp;
    } else {
        temp_table->tail->next = temp;
        temp_table->tail = temp;
    }
    temp->next = NULL;
}

/**
 * Frees all tracked temporary symbols and the temp table itself
 * Should be called after parsing completes to prevent memory leaks
 */
void free_temp_symbols(void) {
    Symbol* current = temp_table->head;
    while (current != NULL) {
        Symbol* next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    temp_table->head = NULL;
    temp_table->tail = NULL;
    free(temp_table);
    temp_table = NULL;
}