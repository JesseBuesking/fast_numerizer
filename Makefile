COPTS=-g
#COPTS=-g -Wall -Werror

NAME=fast_numerizer

OPTIMIZATION?=-O2

STD=-std=c99 -pedantic
WARN=-Wall -W -Wno-missing-field-initializers
OPT=$(OPTIMIZATION)

FINAL_CFLAGS=$(STD) $(WARN) $(OPT) $(DEBUG) $(CFLAGS)
FINAL_LDFLAGS=$(LDFLAGS) $(DEBUG)
FINAL_LIBS=-lm
DEBUG=-g -ggdb

FAST_NUMERIZER_CC=$(CC) $(FINAL_CFLAGS)
FAST_NUMERIZER_LD=$(CC) $(FINAL_LDFLAGS)

CSRC=parser.c read.c readfd.c readfp.c readmem.c readrand.c scan.c scan-dyn.c
CHDR=read.h readfd.h readfp.h readmem.h readrand.h scan.h scan-dyn.h

FAST_NUMERIZER_OBJ=fast_numerizer.o scan.o readmem.o main.o

%.o: %.c
	$(FAST_NUMERIZER_CC) -c $<

all: fast_numerizer

fast_numerizer: scanner.h parser.c $(FAST_NUMERIZER_OBJ)
	$(FAST_NUMERIZER_LD) -o $@ $^ $(FINAL_LIBS)
	#gcc -I .. $(COPTS) -o $@ $(CSRC) main.c

parser.c: parser.yy
	~/repositories/lemon/lemon parser.yy

scanner.h: scanner.re
	re2c scanner.re > scanner.h

clean:
	rm -rf *.o parser.h parser.out parser.c scanner.h fast_numerizer

.PHONY: all clean

valgrind:
	$(MAKE) OPTIMIZATION="-O0" MALLOC="libc"
