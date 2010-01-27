# $Id$
# plain simple Makefile to build exprtest

CXX = g++
LEX = flex
YACC = bison

LEX_ARTIFACTS = Scanner.cpp
YACC_ARTIFACTS = location.hh Parser.cpp Parser.hpp position.hh stack.hh

all: Parser.cpp Scanner.cpp

# Generate scanner and parser

Parser.cpp: Parser.yy
	$(YACC) -o Parser.cpp --defines=Parser.hpp Parser.yy

Scanner.cpp: Scanner.ll
	$(LEX) -o Scanner.cpp Scanner.ll

clean: 
	rm -f $(LEX_ARTIFACTS) $(YACC_ARTIFACTS)

