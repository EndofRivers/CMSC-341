PROJ = Proj3
CX = g++
CXXFLAGS = -g -ansi -Wall

OBJECTS = $(PROJ).o Point.o BBox.o QTNode.o QTree.o

Proj3: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o Proj3

$(PROJ).o: $(PROJ).cpp QTNode.h
	$(CXX) $(CXXFLAGS) -c $(PROJ).cpp

QTree.o: QTree.cpp QTree.h QTNode.h
	$(CXX) $(CXXFLAGS) -c QTree.cpp

QTNode.o: QTNode.cpp QTNode.h BBox.h
	$(CXX) $(CXXFLAGS) -c QTNode.cpp

BBox.o: BBox.cpp BBox.h Point.h
	$(CXX) $(CXXFLAGS) -c BBox.cpp

Point.o: Point.cpp Point.h
	$(CXX) $(CXXFLAGS) -c Point.cpp
clean:
	-rm -f *# *~
cleaner: clean
	-rm -f *.o
cleanest: cleaner
	-rm -f core*; rm -f $(PROJ)
run:
	./Proj3
valgrind:
	valgrind ./Proj3