#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "symbol_table.h"

// Arithmetic operations
Symbol* addition(Symbol* a, Symbol* b);
Symbol* subtraction(Symbol* a, Symbol* b);
Symbol* multiplication(Symbol* a, Symbol* b);
Symbol* division(Symbol* a, Symbol* b);

// Comparison operations
Symbol* comparison(Symbol* a, Symbol* b, char* op);

// Logical operations
Symbol* and(Symbol* a, Symbol* b);
Symbol* or(Symbol* a, Symbol* b);
Symbol* not(Symbol* a);

#endif 