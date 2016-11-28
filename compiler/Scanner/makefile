

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib


SHAREDLIB = ../sharedlib

## hier alle Object Files eintragen
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Scanner.o \
	$(OBJDIR)/TestScanner.o \
	$(OBJDIR)/Token.o

#$(OBJDIR)/xx1.o \
#$(OBJDIR)/xxn.o

OBJSFORSCANNERLIB =  \
	$(LIBDIR)/Scanner.o \
	$(LIBDIR)/Token.o



# Variante mit wenig Makefile-Kenntnissen

# linken der Object-files under shared libraries
#makeTestScanner: $(OBJDIR)/Scanner.o $(OBJDIR)/TestScanner.o
#	em++ -g $(OBJDIR)/Scanner.o $(OBJDIR)/TestScanner.o -L../sharedlib  -lAutomat  -lBuffer -lSymboltable -o $(BINDIR)/ScannerTest
#
#
#
## compilieren der source-files
#$(OBJDIR)/Scanner.o :  $(SRCDIR)/Scanner.cpp
#	@echo "em++ $*.cpp"
#	em++ -g  -c -Wall  -o $(OBJDIR)/Scanner.o  $(SRCDIR)/Scanner.cpp
#
#$(OBJDIR)/TestScanner.o :  $(SRCDIR)/TestScanner.cpp
#	@echo "em++ $*.cpp"
#	em++ -g  -c -Wall  -o $(OBJDIR)/TestScanner.o  $(SRCDIR)/TestScanner.cpp
#



#Variante  mit guten Kenntnissen
makeTestScanner: $(OBJS)
	em++ -g $^ -L../sharedlib  -lAutomat  -lBuffer -lSymboltable -o $(BINDIR)/ScannerTest



# $^ liste der abhaengigkeiten


$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp
	@echo "em++ $*.cpp"
	em++ -g  -c -Wall  -o $@  $<

#
# $@ name des object files
# $< erste abhaengigkeit


# loeschen aller files im verzeichnis $(OBJDIR) und $(LIBDIR) und neu bauen

cleanScanner:
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
	$(MAKE) makeTestScanner



## erstellen der shared library

# erst wichtig fuer den Parser Teil
#
ScannerLib:$(OBJSFORSCANNERLIB)
		em++ -static  -o $(SHAREDLIB)/libScanner.bc. $^
#
#
$(LIBDIR)/%.o :  $(SRCDIR)/%.cpp
	@mkdir -p `dirname $(OBJDIR)/$*.o`
	@echo "em++ $*.cpp"
	em++ -g  -c -fPIC  -o $@  $<

