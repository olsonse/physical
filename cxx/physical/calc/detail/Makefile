# $Id$
# plain simple Makefile to build exprtest

CXX = g++
LEX = flex
BISON = bison

SDIR = pregen-scanner
LEX_ARTIFACTS = $(SDIR)/Scanner.cpp $(SDIR)/FlexLexer.h

PDIR = pregen-parser
BISON_ARTIFACTS = $(PDIR)/location.hh $(PDIR)/Parser.cpp \
                  $(PDIR)/Parser.hpp  $(PDIR)/position.hh \
                  $(PDIR)/stack.hh

all: $(PDIR)/Parser.cpp $(SDIR)/Scanner.cpp

# Generate scanner and parser

pregen-parser/Parser.cpp: Parser.yy
	$(BISON) -o $(PDIR)/Parser.cpp Parser.yy

pregen-scanner/Scanner.cpp: Scanner.ll
	$(LEX) -o $(SDIR)/Scanner.cpp Scanner.ll
	cp /usr/include/FlexLexer.h $(SDIR)/

clean: 
	rm -f $(LEX_ARTIFACTS) $(BISON_ARTIFACTS)

