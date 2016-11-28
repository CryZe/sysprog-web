#
#	baut das komplette Parser-Scanner Projekt
#


AUTOMATDIR = Automat

BUFFERDIR = Buffer

SYMBOLTABLEDIR = Symboltable

SCANNERDIR = Scanner

PARSERDIR = Parser

SHAREDLIB = sharedlib


all:	automatLib bufferLib symboltableLib  scannerLib parserLib parser
	@echo "target all"



clean:
	rm -rf $(AUTOMATDIR)/lib/*
	rm -rf $(BUFFERDIR)/lib/*
	rm -rf $(SYMBOLTABLEDIR)/lib/*
	rm -rf $(SCANNERDIR)/lib/*
	rm -rf $(PARSERDIR)/lib/*
	rm -rf $(AUTOMATDIR)/debug/*
	rm -rf $(BUFFERDIR)/debug/*
	rm -rf $(SYMBOLTABLEDIR)/debug/*
	rm -rf $(SCANNERDIR)/debug/*
	rm -rf $(PARSERDIR)/debug/*
	rm -rf $(SHAREDLIB)/*


parser:
	$(MAKE) -C $(PARSERDIR) makeTestParser

scanner:
	$(MAKE) -C $(SCANNERDIR) makeTestScanner

automatLib:
	$(MAKE) -C $(AUTOMATDIR) AutomatLib


bufferLib:
	$(MAKE) -C $(BUFFERDIR) BufferLib

parserLib:
	$(MAKE) -C $(PARSERDIR) ParserLib

# scannerLib wird erst fuer den Parser Teil benoetigt
scannerLib:
	$(MAKE) -C $(SCANNERDIR) ScannerLib

symboltableLib:
	$(MAKE) -C $(SYMBOLTABLEDIR) SymboltableLib
