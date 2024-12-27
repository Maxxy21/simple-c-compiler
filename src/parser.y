%{
#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "operations.h"

void yyerror(const char *s);
int yylex(void);
extern int line_number;
%}

%union {
    int int_val;
    int bool_val;
    char* string_val;
    DataType type_val;
    struct Symbol* symbol;
}

%token <int_val> INT_LITERAL
%token <bool_val> BOOL_LITERAL
%token <string_val> IDENTIFIER
%token INT BOOL IF ELSE WHILE PRINT RETURN
%token GE LE EQ NE AND OR NOT

%type <type_val> type_specifier
%type <symbol> expression
%type <symbol> simple_expression
%type <symbol> term
%type <symbol> factor

%left OR
%left AND
%nonassoc EQ NE
%nonassoc '>' GE '<' LE
%left '+' '-'
%left '*' '/'
%right NOT UMINUS

%%

program: statement_list
       | /* epsilon */
       ;

statement_list: statement
              | statement_list statement
              ;

statement: declaration ';'
        | assignment ';'
        | if_statement
        | while_statement
        | print_statement ';'
        | return_statement ';'
        ;

declaration: type_specifier IDENTIFIER {
                Symbol* symbol = create_symbol($2, $1);
                add_symbol(symbol);
            }
          | type_specifier IDENTIFIER '=' expression {
                if ($1 != $4->type) {
                    fprintf(stderr, "Error at line %d: Cannot initialize '%s' (%s) with value of type %s\n",
                            line_number, $2,
                            $1 == TYPE_BOOL ? "bool" : "int",
                            $4->type == TYPE_BOOL ? "bool" : "int");
                    exit(1);
                }
                Symbol* symbol = create_symbol($2, $1);
                if ($1 == TYPE_INT) {
                    symbol->value.int_val = $4->value.int_val;
                } else {
                    symbol->value.bool_val = $4->value.bool_val;
                }
                add_symbol(symbol);
            }
          ;

type_specifier: INT  { $$ = TYPE_INT; }
              | BOOL { $$ = TYPE_BOOL; }
              ;

assignment: IDENTIFIER '=' expression {
                Symbol* symbol = lookup_symbol($1);
                if (symbol == NULL) {
                    fprintf(stderr, "Error at line %d: Undefined variable '%s'\n",
                            line_number, $1);
                    exit(1);
                }
                if (symbol->type != $3->type) {
                    fprintf(stderr, "Error at line %d: Cannot assign %s value to %s variable '%s'\n",
                            line_number,
                            $3->type == TYPE_BOOL ? "bool" : "int",
                            symbol->type == TYPE_BOOL ? "bool" : "int",
                            symbol->name);
                    exit(1);
                }
                if (symbol->type == TYPE_INT) {
                    symbol->value.int_val = $3->value.int_val;
                } else {
                    symbol->value.bool_val = $3->value.bool_val;
                }
            }
          ;

if_statement: IF '(' expression ')' '{' statement_list '}' {
                if ($3->type != TYPE_BOOL) {
                    fprintf(stderr, "Error at line %d: Condition in if statement must be boolean, got '%s' (%s)\n",
                            line_number, $3->name, $3->type == TYPE_INT ? "int" : "bool");
                    exit(1);
                }
            }
            | IF '(' expression ')' '{' statement_list '}' ELSE '{' statement_list '}' {
                if ($3->type != TYPE_BOOL) {
                    fprintf(stderr, "Error at line %d: Condition in if statement must be boolean, got '%s' (%s)\n",
                            line_number, $3->name, $3->type == TYPE_INT ? "int" : "bool");
                    exit(1);
                }
            }
            ;

while_statement: WHILE '(' expression ')' '{' statement_list '}' {
                if ($3->type != TYPE_BOOL) {
                    fprintf(stderr, "Error at line %d: Condition in while statement must be boolean, got '%s' (%s)\n",
                            line_number, $3->name, $3->type == TYPE_INT ? "int" : "bool");
                    exit(1);
                }
            }
            ;

print_statement: PRINT expression {
                    if ($2->type == TYPE_INT) {
                        printf("%d\n", $2->value.int_val);
                    } else {
                        printf("%s\n", $2->value.bool_val ? "true" : "false");
                    }
                }
              ;

return_statement: RETURN expression {
                    // Could add type checking here if needed
                }
                | RETURN
                ;

expression: simple_expression
          | expression AND simple_expression { $$ = and($1, $3); }
          | expression OR simple_expression  { $$ = or($1, $3); }
          ;

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

term: factor
    | term '*' factor { $$ = multiplication($1, $3); }
    | term '/' factor { $$ = division($1, $3); }
    ;

factor: INT_LITERAL {
            Symbol* symbol = create_symbol("temp", TYPE_INT);
            symbol->value.int_val = $1;
            $$ = symbol;
        }
      | BOOL_LITERAL {
            Symbol* symbol = create_symbol("temp", TYPE_BOOL);
            symbol->value.bool_val = $1;
            $$ = symbol;
        }
      | IDENTIFIER {
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

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", line_number, s);
    exit(1);
}

int main(void) {
    init_symbol_table();
    yyparse();
    free_symbol_table();
    return 0;
}