#USER KHOA LUONG
#USERNAME KLUON7
GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCES = l9stat.c
SOURCES  = ${CSOURCES} Makefile README
EXECBINS = l9stat
SUBMIT   = submit cmps012b-wm.s14 lab9 ${SOURCES}

all : ${EXECBINS}

% : %.c
	- checksource $<
	${GCC} $< -o $@

clean :
	- rm core

spotless : clean
	- rm ${EXECBINS}

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis
