#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von AutomatTarget und TestAutomatTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestSymboltable: SymboltableTarget TestSymboltableTarget SymtabEntryTarget InfoContainerTarget
	em++ -g debug/Symboltable.o debug/TestSymboltable.o debug/SymtabEntry.o debug/InfoContainer.o -o debug/SymboltableTest


# compilieren des Files Automat.cpp zu Automat.o,
# das Objekt-File ist abhängig von src/Automat.cpp und src/Automat.h
# flag:
# -c --> compilieren
# -Wall --> alle meldungen erzeugen

SymboltableTarget :  src/Symboltable.cpp src/Symboltable.h
	em++ -g  -c -Wall src/Symboltable.cpp -o debug/Symboltable.o


# TestAutomat.o ist abhängig von src/TestAutomat.cpp und src/Automat.h
TestSymboltableTarget :  src/TestSymboltable.cpp src/Symboltable.h
	em++ -g  -c -Wall src/TestSymboltable.cpp  -o debug/TestSymboltable.o

SymtabEntryTarget :  src/SymtabEntry.cpp src/SymtabEntry.h
	em++ -g  -c -Wall src/SymtabEntry.cpp -o debug/SymtabEntry.o

InfoContainerTarget :  src/InfoContainer.cpp src/InfoContainer.h
	em++ -g  -c -Wall src/InfoContainer.cpp -o debug/InfoContainer.o

# loeschen aller files im verzeichnis obj und lib und neu bauen

cleanSymboltable:
	rm -rf obj/*
	rm -rf lib/*
	$(MAKE) makeTestSymboltable


#
# erstellen der shared library
#

SymboltableLib: SymboltableLibTarget SymtabEntryLibTarget InfoContainerLibTarget
		em++ -static lib/Symboltable.o lib/SymtabEntry.o lib/InfoContainer.o -o ../sharedlib/libSymboltable.bc.


# compilieren des Files Automat.cpp zu Automat.o mit dem Flag -fPIC (Position Independant Code)
SymboltableLibTarget :  src/Symboltable.cpp src/Symboltable.h
	em++ -g  -c -fPIC  src/Symboltable.cpp -o lib/Symboltable.o

SymtabEntryLibTarget :  src/SymtabEntry.cpp src/SymtabEntry.h
	em++ -g  -c -fPIC src/SymtabEntry.cpp -o lib/SymtabEntry.o

InfoContainerLibTarget :  src/InfoContainer.cpp src/InfoContainer.h
	em++ -g  -c -fPIC src/InfoContainer.cpp -o lib/InfoContainer.o
