all: fast_numerizer

fast_numerizer: scanner.h parser.c
	g++ -o fast_numerizer main.c

parser.c: parser.yy
	~/repositories/lemon/lemon parser.yy

scanner.h: scanner.re
	re2c scanner.re > scanner.h

clean:
	rm -rf *.o parser.h parser.out parser.c scanner.h fast_numerizer

.PHONY: all clean

