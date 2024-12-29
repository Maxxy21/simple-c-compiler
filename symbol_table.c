#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

extern int line_number;  // line number from lexer.l
static SymbolTable* table;

void init_symbol_table(void) {
    table = (SymbolTable*)malloc(sizeof(SymbolTable));
    table->head = NULL;
    table->tail = NULL;
}

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