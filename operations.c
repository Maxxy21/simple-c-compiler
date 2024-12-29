#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

extern int line_number; //line number from lexer.l

static Symbol *create_temp_result(DataType type) {
    static int temp_counter = 0;
    char temp_name[32];
    sprintf(temp_name, "_temp%d", temp_counter++);
    return create_symbol(temp_name, type);
}

static const char *get_type_name(DataType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_BOOL: return "bool";
        default: return "unknown";
    }
}

Symbol *addition(Symbol *a, Symbol *b) {
    if (a->type != TYPE_INT || b->type != TYPE_INT) {
        fprintf(stderr, "Error at line %d: Cannot perform addition between '%s' (%s) and '%s' (%s)\n",
                line_number,
                a->name, get_type_name(a->type),
                b->name, get_type_name(b->type));
        exit(1);
    }

    Symbol *result = create_temp_result(TYPE_INT);
    result->value.int_val = a->value.int_val + b->value.int_val;
    return result;
}

Symbol *subtraction(Symbol *a, Symbol *b) {
    if (a->type != TYPE_INT || b->type != TYPE_INT) {
        fprintf(stderr, "Error at line %d: Cannot perform subtraction between '%s' (%s) and '%s' (%s)\n",
                line_number,
                a->name, get_type_name(a->type),
                b->name, get_type_name(b->type));
        exit(1);
    }

    Symbol *result = create_temp_result(TYPE_INT);
    result->value.int_val = a->value.int_val - b->value.int_val;
    return result;
}

Symbol *multiplication(Symbol *a, Symbol *b) {
    if (a->type != TYPE_INT || b->type != TYPE_INT) {
        fprintf(stderr, "Error at line %d: Cannot perform multiplication between '%s' (%s) and '%s' (%s)\n",
                line_number,
                a->name, get_type_name(a->type),
                b->name, get_type_name(b->type));
        exit(1);
    }

    Symbol *result = create_temp_result(TYPE_INT);
    result->value.int_val = a->value.int_val * b->value.int_val;
    return result;
}

Symbol *division(Symbol *a, Symbol *b) {
    if (a->type != TYPE_INT || b->type != TYPE_INT) {
        fprintf(stderr, "Error at line %d: Cannot perform division between '%s' (%s) and '%s' (%s)\n",
                line_number,
                a->name, get_type_name(a->type),
                b->name, get_type_name(b->type));
        exit(1);
    }

    if (b->value.int_val == 0) {
        fprintf(stderr, "Error at line %d: Division by zero\n", line_number);
        exit(1);
    }

    Symbol *result = create_temp_result(TYPE_INT);
    result->value.int_val = a->value.int_val / b->value.int_val;
    return result;
}

Symbol *comparison(Symbol *a, Symbol *b, char *op) {
    if (a->type != b->type) {
        fprintf(stderr, "Error at line %d: Cannot compare '%s' (%s) with '%s' (%s)\n",
                line_number,
                a->name, get_type_name(a->type),
                b->name, get_type_name(b->type));
        exit(1);
    }

    Symbol *result = create_temp_result(TYPE_BOOL);

    if (strcmp(op, "<") == 0) {
        result->value.bool_val = a->value.int_val < b->value.int_val;
    } else if (strcmp(op, ">") == 0) {
        result->value.bool_val = a->value.int_val > b->value.int_val;
    } else if (strcmp(op, "<=") == 0) {
        result->value.bool_val = a->value.int_val <= b->value.int_val;
    } else if (strcmp(op, ">=") == 0) {
        result->value.bool_val = a->value.int_val >= b->value.int_val;
    } else if (strcmp(op, "==") == 0) {
        if (a->type == TYPE_INT) {
            result->value.bool_val = a->value.int_val == b->value.int_val;
        } else {
            result->value.bool_val = a->value.bool_val == b->value.bool_val;
        }
    } else if (strcmp(op, "!=") == 0) {
        if (a->type == TYPE_INT) {
            result->value.bool_val = a->value.int_val != b->value.int_val;
        } else {
            result->value.bool_val = a->value.bool_val != b->value.bool_val;
        }
    }

    return result;
}

Symbol *and(Symbol *a, Symbol *b) {
    if (a->type != TYPE_BOOL || b->type != TYPE_BOOL) {
        fprintf(stderr, "Error at line %d: Logical AND requires boolean operands, got '%s' (%s) and '%s' (%s)\n",
                line_number,
                a->name, get_type_name(a->type),
                b->name, get_type_name(b->type));
        exit(1);
    }

    Symbol *result = create_temp_result(TYPE_BOOL);
    result->value.bool_val = a->value.bool_val && b->value.bool_val;
    return result;
}

Symbol *or(Symbol *a, Symbol *b) {
    if (a->type != TYPE_BOOL || b->type != TYPE_BOOL) {
        fprintf(stderr, "Error at line %d: Logical OR requires boolean operands, got '%s' (%s) and '%s' (%s)\n",
                line_number,
                a->name, get_type_name(a->type),
                b->name, get_type_name(b->type));
        exit(1);
    }

    Symbol *result = create_temp_result(TYPE_BOOL);
    result->value.bool_val = a->value.bool_val || b->value.bool_val;
    return result;
}

Symbol *not(Symbol *a) {
    if (a->type != TYPE_BOOL) {
        fprintf(stderr, "Error at line %d: Logical NOT requires boolean operand, got '%s' (%s)\n",
                line_number, a->name, get_type_name(a->type));
        exit(1);
    }

    Symbol *result = create_temp_result(TYPE_BOOL);
    result->value.bool_val = !a->value.bool_val;
    return result;
}
