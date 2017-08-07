# $Id: Makefile,v 1.11 2014-02-13 18:53:02-08 - - $

MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS   = gcc -MM
GRIND    = valgrind --leak-check=full

CHEADER   = cbox.h
CSOURCE   = cbox.c main.c
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = cbox
SOURCES   = ${CHEADER} ${CSOURCE} ${MKFILE}
LISTING   = Listing.cbox.ps

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	cid + $<
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES}

lis : ${SOURCES} test
	mkpspdf ${LISTING} ${SOURCES} test.lis

clean :
	- rm ${OBJECTS} ${DEPSFILE} core test.lis

spotless : clean
	- rm ${EXECBIN} ${LISTING:.ps=.p*} test.lis

test : ${EXECBIN}
	${GRIND} --log-file=test.log ${EXECBIN} >test.out 2>test.err
	more ${DEPSFILE} test.out test.err test.log >test.lis
	- rm test.out test.err test.log

deps : ${CSOURCE} ${CHEADER}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MKDEPS} ${CSOURCE} >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${MAKE} --no-print-directory deps

ifeq ("${NEEDINCL}","")
include ${DEPSFILE}
endif

