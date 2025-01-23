INCLUDE = ../include
SRC     = ../src
CXX     = g++
CPPFLAGS = -I$(INCLUDE) -c
OBJECTS = main.o FileHandler.o DataSection.o DataFile.o DataHandler.o args.o

all: $(OBJECTS)
	$(CXX) -o Notes-Finder $(OBJECTS)

main.o: $(SRC)/main.cpp $(INCLUDE)/main.h
# Some people say do it this way for readability
	$(CXX) $(CPPFLAGS) $(SRC)/main.cpp

FileHandler.o: $(SRC)/FileHandler.cpp $(INCLUDE)/FileHandler.h
# Others say do it this way to reduce (spelling) errors
	$(CXX) $(CPPFLAGS) $<

DataSection.o: $(SRC)/DataSection.cpp $(INCLUDE)/DataSection.h
	$(CXX) $(CPPFLAGS) $<

DataFile.o: $(SRC)/DataFile.cpp $(INCLUDE)/DataFile.h
	$(CXX) $(CPPFLAGS) $<

DataHandler.o: $(SRC)/DataHandler.cpp $(INCLUDE)/DataHandler.h
	$(CXX) $(CPPFLAGS) $<

args.o: $(SRC)/args.cpp $(INCLUDE)/args.h
	$(CXX) $(CPPFLAGS) $<

clean: 
	del *.exe *.o
