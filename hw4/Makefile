quack.tab.c quack.tab.h: quack.y quack.h
	bison -d -v quack.y

lex.yy.c: quack.l quack.tab.h quack.h
	flex quack.l

quack: lex.yy.c quack.tab.c quack.tab.h quack.h
	g++ quack.tab.c lex.yy.c -lfl -o quack
