CC 			= icc
CXXFLAG 	= -O0 -Wall -Wextra -g -std=c++14 -pthread -I.

GTEST_HEADER= gtest/*.h gtest/internal/*.h
GTEST_SRC 	= gsrc/*.cc gsrc/*.h $(GTEST_HEADER)

test 		: test.o Skiplist.o gtest_main.a
	$(CC) $(CXXFLAG) $^ -o $@

Skiplist.o 	: Skiplist.cpp Skiplist.h interface.h
	$(CC) $< -o $@ $(CXXFLAG) -c

test.o 		: test.cpp interface.h
	$(CC) $< -o $@ $(CXXFLAG) -c

gtest_main.a: gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

gtest-all.o : $(GTEST_SRC)
	$(CC) $(CXXFLAG) -c gsrc/gtest-all.cc

gtest_main.o: $(GTEST_SRC)
	$(CC) $(CXXFLAG) -c gsrc/gtest_main.cc

clean		:
	rm -f test.o test Skiplist.o

rebuild		:	clean test

.PHONY		:	clean rebuild
