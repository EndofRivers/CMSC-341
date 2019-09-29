PROJ = Driver
CX = g++
CXXFLAGS = -g -ansi -Wall

OBJECTS = Driver.o ProbeHashTable.o ChainHashTable.o

Driver: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) getCurrentCPU.cpp -o $(PROJ)

Driver.o: Driver.cpp ProbeHashTable.o ChainHashTable.o
	$(CXX) $(CXXFLAGS) -c Driver.cpp

ProbeHashTable.o: ProbeHashTable.cpp ProbeHashTable.h
	$(CXX) $(CXXFLAGS) -c ProbeHashTable.cpp

ChainHashTable.o: ChainHashTable.cpp ChainHashTable.h
	$(CXX) $(CXXFLAGS) -c ChainHashTable.cpp

clean:
	-rm -f *# *~
cleaner: clean
	-rm -f *.o
cleanest: cleaner
	-rm -f core*; rm -f $(PROJ)
run:
	./$(PROJ)
valgrind:
	valgrind ./$(PROJ)