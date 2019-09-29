PROJ = Driver
CX = g++
CXXFLAGS = -g -ansi -Wall

OBJECTS = Driver.o MinMaxHeap.o NoCopyString.o

Driver: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(PROJ)

Driver.o: Driver.cpp MinMaxHeap.o NoCopyString.o
	$(CXX) $(CXXFLAGS) -c Driver.cpp

MinMaxHeap.o: MinMaxHeap.cpp MinMaxHeap.h
	$(CXX) $(CXXFLAGS) -c MinMaxHeap.cpp

NoCopyString.o: NoCopyString.cpp NoCopyString.h
	$(CXX) $(CXXFLAGS) -c NoCopyString.cpp

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