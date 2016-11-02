LEMON=~/repositories/lemon/lemon
RE2C=re2c

$(CC)=gcc
$(CXX)=g++

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

FINAL_CFLAGS=$(STD) $(WARN) $(OPT) $(DEBUG)
FINAL_LDFLAGS=$(LDFLAGS) $(DEBUG)
FINAL_LIBS=
DEBUG=-g -ggdb

FAST_NUMERIZER_CC=$(CC) $(FINAL_CFLAGS)
FAST_NUMERIZER_LD=$(CC) $(FINAL_LDFLAGS)

CSRC=parser.c read.c readfd.c readfp.c readmem.c readrand.c scan.c scan-dyn.c
CHDR=read.h readfd.h readfp.h readmem.h readrand.h scan.h scan-dyn.h

FAST_NUMERIZER_OBJ=parser.o scan.o readmem.o fast_numerizer.o scanner.o sds.o num-fmt.o
DEPS=parser.h scan.h readmem.h fast_numerizer.h scanner.h

TEST_FILES=test_basic.yaml

%.o: %.c $(DEPS)
	$(FAST_NUMERIZER_CC) -c $<

all: fast_numerizer

fast_numerizer: $(FAST_NUMERIZER_OBJ) main.o
	$(FAST_NUMERIZER_LD) $^ -o $@ $(FINAL_LIBS)
	./fast_numerizer

parser.h: parser.yy
	# produces parser.c and parser.h
	$(LEMON) parser.yy

parser.o: parser.h
	# produces parser.o
	$(FAST_NUMERIZER_CC) -c parser.c

scanner.c: scanner.re
	$(RE2C) -o $@ scanner.re

clean:
	rm -rf *.o parser.h parser.out parser.c scanner.o scanner.c main.o fast_numerizer *.gch test_fast_numerizer

.PHONY: all clean

test_fast_numerizer.o: parser.h scan.h readmem.h fast_numerizer.h scanner.h test_fast_numerizer.c
	$(CXX) -std=c++11 -L/usr/local/include -I$(GTEST_DIR)/include -c test_fast_numerizer.c -lyaml-cpp

test_fast_numerizer: $(FAST_NUMERIZER_OBJ) $(GTEST_DIR)/make/gtest_main.a test_fast_numerizer.o
	$(CXX) -std=c++11 -L/usr/local/include -o $@ -I$(GTEST_DIR)/include -I. $^ -pthread -lyaml-cpp

test: all test_fast_numerizer $(TEST_FILES)
	./test_fast_numerizer

valgrind:
	$(MAKE) OPTIMIZATION="-O0" MALLOC="libc"
