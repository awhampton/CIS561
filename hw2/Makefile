quack.tab.c quack.tab.h: quack.y
	bison -d -v quack.y

lex.yy.c: quack.l quack.tab.h
	flex quack.l

quack: lex.yy.c quack.tab.c quack.tab.h
	g++ quack.tab.c lex.yy.c -lfl -o quack
