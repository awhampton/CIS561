PROGNAME=quack

${PROGNAME}: lex.yy.c ${PROGNAME}.tab.c ${PROGNAME}.tab.h ${PROGNAME}.h
	g++ ${PROGNAME}.tab.c lex.yy.c -lfl -o ${PROGNAME}

${PROGNAME}.tab.c ${PROGNAME}.tab.h: ${PROGNAME}.y ${PROGNAME}.h
	bison -d -v ${PROGNAME}.y

lex.yy.c: ${PROGNAME}.l ${PROGNAME}.tab.h ${PROGNAME}.h
	flex ${PROGNAME}.l

clean:
	rm -f *.o *.tab.* *.yy.* ${PROGNAME} ${PROGNAME}.output
