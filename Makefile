CC 			:= icc
CXXFLAG 	:= -O0 -Wall -Wextra -g

all			:	Skiplist

Skiplist.o 	:	Skiplist.cpp
	$(CC) $^ -o $@ $(CXXFLAG) -c

clean		:
	rm -f  *.o Skiplist

rebuild		:	clean all

.PHONY		:	all clean rebuild