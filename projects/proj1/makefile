CX = g++
CXXFLAGS = -Wall

proj1: SSLColumn.o SortedSquareList.o proj1.cpp
	$(CXX) $(CXXFLAGS) SSLColumn.o SortedSquareList.o proj1.cpp -o proj1

SortedSquareList.o: SSLColumn.o SortedSquareList.cpp SortedSquareList.h
	$(CXX) $(CXXFLAGS) -c SortedSquareList.cpp

SSLColumn.o: SSLColumn.cpp SSLColumn.h
	$(CXX) $(CXXFLAGS) -c SSLColumn.cpp

clean:
	rm *.o*
	rm *~

run:
	./proj1