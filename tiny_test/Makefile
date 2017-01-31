tt.tab.c tt.tab.h: tt.y tt.h
	bison -d -v tt.y

lex.yy.c: tt.l tt.tab.h tt.h
	flex tt.l

tt: lex.yy.c tt.tab.c tt.tab.h tt.h
	g++ tt.tab.c lex.yy.c -lfl -o tiny_test
