%{
// Include necessary header files
#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "operations.h"

// Function declarations
void yyerror(const char *s);
int yylex(void);
// Line number from lexer for error reporting
extern int line_number;
%}

// Define possible types that our grammar symbols can have
%union {
    int int_val;           // Integer values
    int bool_val;          // Boolean values (0 or 1)
    char* string_val;      // String values (for identifiers)
    DataType type_val;     // Data types (TYPE_INT or TYPE_BOOL)
    struct Symbol* symbol; // Symbol table entries
}

// Token definitions with their types
%token <int_val> INT_LITERAL     // Integer constants
%token <bool_val> BOOL_LITERAL   // Boolean constants
%token <string_val> IDENTIFIER   // Variable names
%token INT BOOL IF ELSE WHILE PRINT RETURN  // Keywords
%token GE LE EQ NE AND OR NOT    // Operators

// Define types for non-terminals
%type <type_val> type_specifier
%type <symbol> expression
%type <symbol> simple_expression
%type <symbol> term
%type <symbol> factor

// Operator precedence (lowest to highest)
%left OR             // Logical OR
%left AND            // Logical AND
%nonassoc EQ NE      // Equality operators
%nonassoc '>' GE '<' LE  // Comparison operators
%left '+' '-'        // Addition and subtraction
%left '*' '/'        // Multiplication and division
%right NOT UMINUS    // Unary operators

%%

// Grammar Rules Section

// Program can be a list of statements or empty
program: statement_list
       | /* epsilon */
       ;

// Multiple statements or single statement
statement_list: statement
              | statement_list statement
              ;

// Different types of statements
statement: declaration ';'
        | assignment ';'
        | if_statement
        | while_statement
        | print_statement ';'
        | return_statement ';'
        ;

// Variable declarations with optional initialization
declaration: type_specifier IDENTIFIER {
                // Create and add new symbol to table
                Symbol* symbol = create_symbol($2, $1);
                add_symbol(symbol);
            }
          | type_specifier IDENTIFIER '=' expression {
                // Check if initialization type matches declaration
                if ($1 != $4->type) {
                    fprintf(stderr, "Error at line %d: Cannot initialize '%s' (%s) with value of type %s\n",
                            line_number, $2,
                            $1 == TYPE_BOOL ? "bool" : "int",
                            $4->type == TYPE_BOOL ? "bool" : "int");
                    exit(1);
                }
                // Create symbol and initialize with value
                Symbol* symbol = create_symbol($2, $1);
                if ($1 == TYPE_INT) {
                    symbol->value.int_val = $4->value.int_val;
                } else {
                    symbol->value.bool_val = $4->value.bool_val;
                }
                add_symbol(symbol);
            }
          ;

// Data types supported by our language
type_specifier: INT  { $$ = TYPE_INT; }
              | BOOL { $$ = TYPE_BOOL; }
              ;

// Variable assignment with type checking
assignment: IDENTIFIER '=' expression {
                // Check if variable exists
                Symbol* symbol = lookup_symbol($1);
                if (symbol == NULL) {
                    fprintf(stderr, "Error at line %d: Undefined variable '%s'\n",
                            line_number, $1);
                    exit(1);
                }
                // Check if types match
                if (symbol->type != $3->type) {
                    fprintf(stderr, "Error at line %d: Cannot assign %s value to %s variable '%s'\n",
                            line_number,
                            $3->type == TYPE_BOOL ? "bool" : "int",
                            symbol->type == TYPE_BOOL ? "bool" : "int",
                            symbol->name);
                    exit(1);
                }
                // Assign value based on type
                if (symbol->type == TYPE_INT) {
                    symbol->value.int_val = $3->value.int_val;
                } else {
                    symbol->value.bool_val = $3->value.bool_val;
                }
            }
          ;

// If statement with optional else branch
if_statement: IF '(' expression ')' '{' statement_list '}' {
                // Check if condition is boolean
                if ($3->type != TYPE_BOOL) {
                    fprintf(stderr, "Error at line %d: Condition in if statement must be boolean, got '%s' (%s)\n",
                            line_number, $3->name, $3->type == TYPE_INT ? "int" : "bool");
                    exit(1);
                }
            }
            | IF '(' expression ')' '{' statement_list '}' ELSE '{' statement_list '}' {
                // Check if condition is boolean (same as above)
                if ($3->type != TYPE_BOOL) {
                    fprintf(stderr, "Error at line %d: Condition in if statement must be boolean, got '%s' (%s)\n",
                            line_number, $3->name, $3->type == TYPE_INT ? "int" : "bool");
                    exit(1);
                }
            }
            ;

// While loop with condition checking
while_statement: WHILE '(' expression ')' '{' statement_list '}' {
                // Check if condition is boolean
                if ($3->type != TYPE_BOOL) {
                    fprintf(stderr, "Error at line %d: Condition in while statement must be boolean, got '%s' (%s)\n",
                            line_number, $3->name, $3->type == TYPE_INT ? "int" : "bool");
                    exit(1);
                }
            }
            ;

// Print statement that handles both types
print_statement: PRINT expression {
                    if ($2->type == TYPE_INT) {
                        printf("%d\n", $2->value.int_val);
                    } else {
                        printf("%s\n", $2->value.bool_val ? "true" : "false");
                    }
                }
              ;

// Return statement (could add type checking if needed)
return_statement: RETURN expression
                | RETURN
                ;

// Expression handling with logical operators
expression: simple_expression
          | expression AND simple_expression { $$ = and($1, $3); }
          | expression OR simple_expression  { $$ = or($1, $3); }
          ;

// Simple expressions including arithmetic and comparisons
simple_expression: term
                | simple_expression '+' term { $$ = addition($1, $3); }
                | simple_expression '-' term { $$ = subtraction($1, $3); }
                | simple_expression '>' term { $$ = comparison($1, $3, ">"); }
                | simple_expression '<' term { $$ = comparison($1, $3, "<"); }
                | simple_expression GE term  { $$ = comparison($1, $3, ">="); }
                | simple_expression LE term  { $$ = comparison($1, $3, "<="); }
                | simple_expression EQ term  { $$ = comparison($1, $3, "=="); }
                | simple_expression NE term  { $$ = comparison($1, $3, "!="); }
                ;

// Terms for multiplication and division
term: factor
    | term '*' factor { $$ = multiplication($1, $3); }
    | term '/' factor { $$ = division($1, $3); }
    ;

// Basic factors include literals, variables, and expressions
factor: INT_LITERAL {
            // Create temporary symbol for integer literal
            Symbol* symbol = create_symbol("temp", TYPE_INT);
            symbol->value.int_val = $1;
            $$ = symbol;
        }
      | BOOL_LITERAL {
            // Create temporary symbol for boolean literal
            Symbol* symbol = create_symbol("temp", TYPE_BOOL);
            symbol->value.bool_val = $1;
            $$ = symbol;
        }
      | IDENTIFIER {
            // Look up variable in symbol table
            Symbol* symbol = lookup_symbol($1);
            if (symbol == NULL) {
                fprintf(stderr, "Error at line %d: Undefined variable '%s'\n",
                        line_number, $1);
                exit(1);
            }
            $$ = symbol;
        }
      | '(' expression ')' { $$ = $2; }
      | NOT factor        { $$ = not($2); }
      | '-' factor %prec UMINUS {
            // Check if operand is integer for unary minus
            if ($2->type != TYPE_INT) {
                fprintf(stderr, "Error at line %d: Unary minus cannot be applied to '%s' (%s)\n",
                        line_number, $2->name, "bool");
                exit(1);
            }
            Symbol* result = create_symbol("temp", TYPE_INT);
            result->value.int_val = -$2->value.int_val;
            $$ = result;
        }
      ;

%%

// Error handling function
void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", line_number, s);
    exit(1);
}

// Main function - initialize, parse, cleanup
int main(void) {
    init_symbol_table();
    yyparse();
    free_symbol_table();
    return 0;
}