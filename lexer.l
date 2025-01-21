%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "parser.tab.h"

void yyerror(char *);
// Track current line number for error reporting
int line_number = 1;
%}

// Flex options
%option nounput   // Don't generate unput function
%option noinput   // Don't generate input function
%option noyywrap  // Don't use yywrap function

DIGIT       [0-9]                           // Single digit
INT         {DIGIT}+                        // Integer number
LETTER      [a-zA-Z]                        // Single letter
ID          {LETTER}({LETTER}|{DIGIT})*     // Identifier pattern
WHITESPACE  [ \t\r]                         // Whitespace characters

%%

"//".*          ; /* Single line comments - skips them */
{WHITESPACE}+   ; /* Skip whitespace */
\n              { line_number++; }

"int"           { return INT; }
"bool"          { return BOOL; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"print"         { return PRINT; }
"return"        { return RETURN; }
"true"          { yylval.bool_val = 1; return BOOL_LITERAL; }
"false"         { yylval.bool_val = 0; return BOOL_LITERAL; }

{INT}           {
                  yylval.int_val = atoi(yytext);
                  return INT_LITERAL;
                }

{ID}            {
                  yylval.string_val = strdup(yytext);
                  return IDENTIFIER;
                }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"="             { return '='; }
";"             { return ';'; }
"{"             { return '{'; }
"}"             { return '}'; }
"("             { return '('; }
")"             { return ')'; }
">"             { return '>'; }
"<"             { return '<'; }
">="            { return GE; }
"<="            { return LE; }
"=="            { return EQ; }
"!="            { return NE; }
"&&"            { return AND; }
"||"            { return OR; }
"!"             { return NOT; }

.               { printf("Unrecognized character: %s\n", yytext);
                 yyerror("lexical error");
               }

%%

