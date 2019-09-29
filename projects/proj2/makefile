CX = g++
CXXFLAGS = -Wall

main: Int341.o DNode.o INode.o SqList.o main.cpp
	$(CXX) $(CXXFLAGS) Int341.o DNode.o INode.o SqList.o main.cpp -o main

SqList.o: SqList.cpp SqList.h INode.o
	$(CXX) $(CXXFLAGS) -c SqList.cpp

INode.o: INode.cpp INode.h DNode.o
	$(CXX) $(CXXFLAGS) -c INode.cpp

DNode.o: DNode.cpp DNode.h Int341.o
	$(CXX) $(CXXFLAGS) -c DNode.cpp

Int341.o: Int341.cpp Int341.h
	$(CXX) $(CXXFLAGS) -c Int341.cpp
clean:
	rm *.o*
	rm *~

run:
	./main