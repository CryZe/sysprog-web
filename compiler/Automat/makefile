#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von AutomatTarget und TestAutomatTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestAutomat: AutomatTarget TestAutomatTarget StateTarget LexemTarget
	em++ -g4 debug/Automat.o debug/TestAutomat.o debug/State.o debug/Lexem.o -o debug/AutomatTest


# compilieren des Files Automat.cpp zu Automat.o,
# das Objekt-File ist abhängig von src/Automat.cpp und src/Automat.h
# flag:
# -c --> compilieren
# -Wall --> alle meldungen erzeugen

AutomatTarget :  src/Automat.cpp src/Automat.h
	em++ -g4  -c -Wall src/Automat.cpp -o debug/Automat.o


# TestAutomat.o ist abhängig von src/TestAutomat.cpp und src/Automat.h
TestAutomatTarget :  src/TestAutomat.cpp src/Automat.h
	em++ -g4  -c -Wall src/TestAutomat.cpp  -o debug/TestAutomat.o

# Test Build state.cpp
StateTarget :  src/State.cpp src/State.h
	em++ -g4  -c -Wall src/State.cpp  -o debug/State.o

LexemTarget :  src/Lexem.cpp src/Lexem.h
	em++ -g4  -c -Wall src/Lexem.cpp  -o debug/Lexem.o


# loeschen aller files im verzeichnis obj und lib und neu bauen

cleanAutomat:
	rm -rf obj/*
	rm -rf lib/*
	$(MAKE) makeTestAutomat


#
# erstellen der shared library
#

AutomatLib: AutomatLibTarget StateLibTarget LexemLibTarget
		em++ -static lib/Automat.o  lib/State.o lib/Lexem.o -o ../sharedlib/libAutomat.bc.


# compilieren des Files Automat.cpp zu Automat.o mit dem Flag -fPIC (Position Independant Code)
AutomatLibTarget :  src/Automat.cpp src/Automat.h
	em++ -g4  -c -fPIC  src/Automat.cpp -o lib/Automat.o

StateLibTarget :  src/State.cpp src/State.h
	em++ -g4  -c -fPIC src/State.cpp  -o lib/State.o

LexemLibTarget :  src/Lexem.cpp src/Lexem.h
	em++ -g4  -c -fPIC src/Lexem.cpp  -o lib/Lexem.o

