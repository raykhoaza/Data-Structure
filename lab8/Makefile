#USER: KHOA LUONG
#USERNAME: KLUON7
MKFILE    = Makefile

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
GRIND     = valgrind --leak-check=full

CSOURCE   = numsort.c linesort.c inssort.c
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = numsort linesort
SOURCES   = ${CSOURCE} ${MKFILE}
SUBMIT    = submit cmps012b-wm.w14 lab9

all : ${EXECBIN}

linesort : linesort.o inssort.o

numsort : numsort.o inssort.o

%.o : %.c
	cid + $<
	${GCC} -c $<

ci : ${CSOURCE}
	checksource ${CSOURCE}
	ci ${CSOURCE}
	
submit : ${SOURCES}
	${SUBMIT} ${SOURCES}


