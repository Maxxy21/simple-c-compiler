#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

// Helper function to create temporary result
static Symbol* create_temp_result(DataType type) {
    static int temp_counter = 0;
    char temp_name[32];
    sprintf(temp_name, "_temp%d", temp_counter++);
    return create_symbol(temp_name, type);
}

Symbol* addition(Symbol* a, Symbol* b) {
    if (a->type != TYPE_INT || b->type != TYPE_INT) {
        fprintf(stderr, "Error: Addition requires integer operands\n");
        exit(1);
    }

    Symbol* result = create_temp_result(TYPE_INT);
    result->value.int_val = a->value.int_val + b->value.int_val;
    return result;
}

Symbol* subtraction(Symbol* a, Symbol* b) {
    if (a->type != TYPE_INT || b->type != TYPE_INT) {
        fprintf(stderr, "Error: Subtraction requires integer operands\n");
        exit(1);
    }

    Symbol* result = create_temp_result(TYPE_INT);
    result->value.int_val = a->value.int_val - b->value.int_val;
    return result;
}

Symbol* multiplication(Symbol* a, Symbol* b) {
    if (a->type != TYPE_INT || b->type != TYPE_INT) {
        fprintf(stderr, "Error: Multiplication requires integer operands\n");
        exit(1);
    }

    Symbol* result = create_temp_result(TYPE_INT);
    result->value.int_val = a->value.int_val * b->value.int_val;
    return result;
}

Symbol* division(Symbol* a, Symbol* b) {
    if (a->type != TYPE_INT || b->type != TYPE_INT) {
        fprintf(stderr, "Error: Division requires integer operands\n");
        exit(1);
    }

    if (b->value.int_val == 0) {
        fprintf(stderr, "Error: Division by zero\n");
        exit(1);
    }

    Symbol* result = create_temp_result(TYPE_INT);
    result->value.int_val = a->value.int_val / b->value.int_val;
    return result;
}

Symbol* comparison(Symbol* a, Symbol* b, char* op) {
    if (a->type != b->type) {
        fprintf(stderr, "Error: Cannot compare different types\n");
        exit(1);
    }

    Symbol* result = create_temp_result(TYPE_BOOL);

    if (strcmp(op, "<") == 0) {
        result->value.bool_val = a->value.int_val < b->value.int_val;
    }
    else if (strcmp(op, ">") == 0) {
        result->value.bool_val = a->value.int_val > b->value.int_val;
    }
    else if (strcmp(op, "<=") == 0) {
        result->value.bool_val = a->value.int_val <= b->value.int_val;
    }
    else if (strcmp(op, ">=") == 0) {
        result->value.bool_val = a->value.int_val >= b->value.int_val;
    }
    else if (strcmp(op, "==") == 0) {
        if (a->type == TYPE_INT) {
            result->value.bool_val = a->value.int_val == b->value.int_val;
        } else {
            result->value.bool_val = a->value.bool_val == b->value.bool_val;
        }
    }
    else if (strcmp(op, "!=") == 0) {
        if (a->type == TYPE_INT) {
            result->value.bool_val = a->value.int_val != b->value.int_val;
        } else {
            result->value.bool_val = a->value.bool_val != b->value.bool_val;
        }
    }

    return result;
}

Symbol* and(Symbol* a, Symbol* b) {
    if (a->type != TYPE_BOOL || b->type != TYPE_BOOL) {
        fprintf(stderr, "Error: AND operation requires boolean operands\n");
        exit(1);
    }

    Symbol* result = create_temp_result(TYPE_BOOL);
    result->value.bool_val = a->value.bool_val && b->value.bool_val;
    return result;
}

Symbol* or(Symbol* a, Symbol* b) {
    if (a->type != TYPE_BOOL || b->type != TYPE_BOOL) {
        fprintf(stderr, "Error: OR operation requires boolean operands\n");
        exit(1);
    }

    Symbol* result = create_temp_result(TYPE_BOOL);
    result->value.bool_val = a->value.bool_val || b->value.bool_val;
    return result;
}

Symbol* not(Symbol* a) {
    if (a->type != TYPE_BOOL) {
        fprintf(stderr, "Error: NOT operation requires boolean operand\n");
        exit(1);
    }

    Symbol* result = create_temp_result(TYPE_BOOL);
    result->value.bool_val = !a->value.bool_val;
    return result;
}