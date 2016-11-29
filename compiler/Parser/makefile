

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib


SHAREDLIB = ../sharedlib

## hier alle Object Files eintragen
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Parser.o \
	$(OBJDIR)/TestParser.o \
	$(OBJDIR)/Declarations.o \
	$(OBJDIR)/Expression.o \
	$(OBJDIR)/ParseTree.o \
	$(OBJDIR)/Statements.o \
	$(OBJDIR)/UnexpectedToken.o \
	$(OBJDIR)/TypecheckError.o


#$(OBJDIR)/xx1.o \
#$(OBJDIR)/xxn.o

OBJSFORPARSERLIB =  \
	$(LIBDIR)/Parser.o



# Variante mit wenig Makefile-Kenntnissen

# linken der Object-files under shared libraries
#makeTestScanner: $(OBJDIR)/Scanner.o $(OBJDIR)/TestScanner.o
#	em++ -g4 $(OBJDIR)/Scanner.o $(OBJDIR)/TestScanner.o -L../sharedlib  -lAutomat  -lBuffer -lSymboltable -o $(BINDIR)/ScannerTest
#
#
#
## compilieren der source-files
#$(OBJDIR)/Scanner.o :  $(SRCDIR)/Scanner.cpp
#	@echo "em++ $*.cpp"
#	em++ -g4  -c -Wall  -o $(OBJDIR)/Scanner.o  $(SRCDIR)/Scanner.cpp
#
#$(OBJDIR)/TestScanner.o :  $(SRCDIR)/TestScanner.cpp
#	@echo "em++ $*.cpp"
#	em++ -g4  -c -Wall  -o $(OBJDIR)/TestScanner.o  $(SRCDIR)/TestScanner.cpp
#



#Variante  mit guten Kenntnissen
makeTestParser: $(OBJS)
	em++ -g4 $^ \
	../Automat/lib/Automat.o \
	../Automat/lib/Lexem.o \
	../Automat/lib/State.o \
	../Buffer/lib/Buffer.o \
	../Scanner/lib/Scanner.o \
	../Scanner/lib/Token.o \
	../Symboltable/lib/InfoContainer.o \
	../Symboltable/lib/Symboltable.o \
	../Symboltable/lib/SymtabEntry.o \
	-o $(BINDIR)/ParserTest.js
	emar rcs $(BINDIR)/libParserTest.a $^ \
	../Automat/lib/Automat.o \
	../Automat/lib/Lexem.o \
	../Automat/lib/State.o \
	../Buffer/lib/Buffer.o \
	../Scanner/lib/Scanner.o \
	../Scanner/lib/Token.o \
	../Symboltable/lib/InfoContainer.o \
	../Symboltable/lib/Symboltable.o \
	../Symboltable/lib/SymtabEntry.o


# $^ liste der abhaengigkeiten


$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp
	@echo "em++ $*.cpp"
	em++ -g4  -c -Wall  -o $@  $<

#
# $@ name des object files
# $< erste abhaengigkeit


# loeschen aller files im verzeichnis $(OBJDIR) und $(LIBDIR) und neu bauen

cleanParser:
	rm -rf $(OBJDIR)/*
	$(MAKE) makeTestParser



## erstellen der shared library

# erst wichtig fuer den Parser Teil
#
ParserLib:$(OBJSFORPARSERLIB)
		em++ -static  -o $(SHAREDLIB)/libParser.bc. $^
#
#
$(LIBDIR)/%.o :  $(SRCDIR)/%.cpp
	@mkdir -p `dirname $(OBJDIR)/$*.o`
	@echo "em++ $*.cpp"
	em++ -g4  -c -fPIC  -o $@  $<

