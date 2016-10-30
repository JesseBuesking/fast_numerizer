COPTS=-g
#COPTS=-g -Wall -Werror

GTEST_DIR=$(HOME)/repositories/googletest/googletest
GTEST_HEADERS=$(GTEST_DIR)/include/gtest/*.h \
			  $(GTEST_DIR)/include/gtest/internal/*.h

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

FAST_NUMERIZER_OBJ=parser.o scan.o readmem.o fast_numerizer.o

%.o: %.c
	$(FAST_NUMERIZER_CC) -c $<

all: clean fast_numerizer

fast_numerizer: scanner.h $(FAST_NUMERIZER_OBJ) main.o
	$(FAST_NUMERIZER_LD) $^ -o $@ $(FINAL_LIBS)
	echo "\n"
	./fast_numerizer
	echo "\n"

parser.o: parser.yy
	# produces parser.c
	~/repositories/lemon/lemon parser.yy
	# produces parser.o
	$(FAST_NUMERIZER_CC) -c parser.c

scanner.h: scanner.re
	re2c scanner.re > scanner.h

clean:
	rm -rf *.o parser.h parser.out parser.c scanner.h fast_numerizer

.PHONY: all clean

#test_fast_numerizer: scanner.h fast_numerizer.h test_fast_numerizer.c $(FAST_NUMERIZER_OBJ) $(GTEST_DIR)/make/gtest_main.a
	#g++ -I$(GTEST_DIR)/include -pthread $^ -o $@

test_fast_numerizer.o: test_fast_numerizer.c
	g++ -I$(GTEST_DIR)/include -c test_fast_numerizer.c

test_fast_numerizer: $(FAST_NUMERIZER_OBJ) $(GTEST_DIR)/make/gtest_main.a test_fast_numerizer.o scanner.h fast_numerizer.h
	g++ -I$(GTEST_DIR)/include -pthread $^ -o $@

test: clean all test_fast_numerizer
	./test_fast_numerizer

valgrind:
	$(MAKE) OPTIMIZATION="-O0" MALLOC="libc"
