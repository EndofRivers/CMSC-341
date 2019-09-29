#ifndef _MINMAXHEAP_H_
#define _MINMAXHEAP_H_

#include <iostream>
#include <cmath>

using namespace std;
// Nicholas J Long
// UMBC CMSC 341, Spring 2018
// nlong2@umbc.edu

template <class T> 
bool heapCheck( int value );

template <class T>
class MinMaxHeap {
 public:
  class Heap {
  public:
    Heap(); // Default Constructor
    Heap( int capacity );
    ~Heap(); // Destructor
    void setTwin( Heap *twin); // debug Function
    T getArrayPos( int pos ); // returns root of heap
    int getIndexPos( int pos ); // returns position of root in twin
    int getParent( int index ); // Finds the Parent in Array
    int getLeft( int index ); // Finds the Left in Array
    int getRight( int index ); // Finds the Right in Array
    void bubbleUp(); // Bubbles up the Heap
    void bubbleDown(); // Bubbles down the Heap
    void swap( int child, int parent ); // Swaps parent and child
    void insert ( const T& data ); // Insert into the Heap
    T deleteValue(); // Deletes a value from the minmaxheap
    int size(); // returns size
    void dump(); // dumps heap
    //  private:
    T minKey;
    bool minVal;
    T maxKey;
    bool maxVal;
    int insertCount;
    bool(*heapCheckPtr)( T value , T key );
    Heap *m_twin; // Twin to the Heap
    T *m_array; // Heap Array
    int *m_arrayIndex; // Index of Elements
    int m_size; // Number of Elements in Heap
    int m_capacity; // Capacity of Heap
  };
  MinMaxHeap(); // Default Constructor
  MinMaxHeap( int capacity ); // Overloaded Constructor
  MinMaxHeap( const MinMaxHeap<T>& other); // Copy Constructor
  ~MinMaxHeap(); // Destructor
  const MinMaxHeap<T>& operator=( const MinMaxHeap<T>& rhs); // Overloaded Assignment OP
  int size(); // returns size
  void insert( const T& data); // inserts data/object
  T deleteMin(); // deletes the Min object
  T deleteMax(); // dlete the Max object
  void dump(); // dumps heap
  void locateMin( int pos, T& data, int& index ); // Finds Min object
  void locateMax( int pas, T& data, int& index ); // FInds Max object
  // private:
  int m_size; // Number of elements in heap
  int m_capacity; // Capacity of heap
  Heap *m_N; // Heap Pointer
  Heap *m_X; // Heap Pointer
};

#include "MinMaxHeap.cpp"
#endif
