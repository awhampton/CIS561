PROGNAME=quack

${PROGNAME}: lex.yy.c ${PROGNAME}.tab.c ${PROGNAME}.tab.h ${PROGNAME}.h log.h
	g++ -g -std=c++11 -fmax-errors=3 ${PROGNAME}.tab.c lex.yy.c -lfl -o ${PROGNAME}

${PROGNAME}.tab.c ${PROGNAME}.tab.h: ${PROGNAME}.y ${PROGNAME}.h
	bison -d -v ${PROGNAME}.y

lex.yy.c: ${PROGNAME}.l ${PROGNAME}.tab.h ${PROGNAME}.h
	flex ${PROGNAME}.l

result: generated.c Builtins.h Builtins.c
	gcc generated.c Builtins.c -o compiled_quack

clean:
	rm -f *.o *.tab.* *.yy.* ${PROGNAME} ${PROGNAME}.output
