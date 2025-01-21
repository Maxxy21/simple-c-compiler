# Language Grammar

## Program Structure

program -> statement_list
| ε

statement_list -> statement
| statement_list statement

## Statements

statement -> declaration ;
| assignment ;
| if_statement
| while_statement
| print_statement ;
| return_statement ;

## Declarations and Assignments

declaration -> type_specifier IDENTIFIER
| type_specifier IDENTIFIER = expression

type_specifier -> int | bool

assignment -> IDENTIFIER = expression

## Control Structures
if_statement -> IF ( expression ) { statement_list }
| IF ( expression ) { statement_list } ELSE { statement_list }

while_statement -> WHILE ( expression ) { statement_list }

## IO and Control Flow
print_statement -> PRINT expression

return_statement -> RETURN
| RETURN expression

## Expressions
expression -> simple_expression
| expression AND simple_expression
| expression OR simple_expression

simple_expression -> term
| simple_expression + term
| simple_expression - term
| simple_expression > term
| simple_expression < term
| simple_expression >= term
| simple_expression <= term
| simple_expression == term
| simple_expression != term

term -> factor
| term * factor
| term / factor

factor -> INT_LITERAL
| BOOL_LITERAL
| IDENTIFIER
| ( expression )
| NOT factor
| - factor

## Terminals

INT_LITERAL -> [0-9]+
BOOL_LITERAL -> true | false
IDENTIFIER -> [a-zA-Z][a-zA-Z0-9_]*