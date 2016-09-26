#--------------------------------------------
# makefile zur Erzeugung der .exe zur SRJ
# incl. LaTEX-Teil zur Erstellung von PDF
#--------------------------------------------
.PHONY: all clean

# Definition der Variablen
CXX := g++
CXXFLAGS := -std=c++11 -c -Wall -IS:\Datenban\Wetter\Programme\srj\1.1\lib\\
LDFLAGS := -g -static
HEADERS := $(wildcard S\:\Datenban\Wetter\Programme\srj\1.1\lib\*.h)
objs := main.o file_creation.o Date.o output_latex.o

all: srj_v1-1.exe

# Ziel 1
srj_v1-1.exe: $(objs)
	$(CXX) $(LDFLAGS) -o $@ $^

# Ziel 2
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $<

# Ziel 3
file_creation.o: file_creation.cpp 
	$(CXX) $(CXXFLAGS) $<

# Ziel 4
Date.o: Date.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $<

# Ziel 5
output_latex.o: output_latex.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $<

# Alle *.o Dateien löschen
clean:
	del $(objs)

