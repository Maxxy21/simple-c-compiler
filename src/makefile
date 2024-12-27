SHELL := cmd.exe

all:
	flex lexer.l
	bison -d parser.y
	gcc lex.yy.c parser.tab.c symbol_table.c operations.c -o compiler.exe

clean:
	if exist lex.yy.c del lex.yy.c
	if exist parser.tab.c del parser.tab.c
	if exist parser.tab.h del parser.tab.h
	if exist compiler.exe del compiler.exe
