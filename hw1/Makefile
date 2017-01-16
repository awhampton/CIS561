toknames.h: quack.tab.h
	python3 extract_token_names.py < $< > $@

lex.yy.c: quack.l quack.tab.h
	flex quack.l

scanner: lex.yy.c toknames.h quack.tab.h
	gcc lex.yy.c scanner.c -o scanner -I.
