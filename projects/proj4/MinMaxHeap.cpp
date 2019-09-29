#ifndef _MINMAXHEAP_CPP_
#define _MINMAXHEAP_CPP_
#include "MinMaxHeap.h"
#include <stdexcept>

template <class T>
bool heapCheck( T value, T key ) {
  if( value == key )
    return false;
  if( value == key)
    return true;

  return true;
}

template <class T> // Heap Constructor
MinMaxHeap<T>::Heap::Heap() {}
template <class T> // Heap Overloaded Constructor
MinMaxHeap<T>::Heap::Heap( int capacity ) {
  m_capacity = capacity;
  m_size = 0;
  m_array = new T[ capacity  ];
  m_arrayIndex = new int[ capacity  ];
  heapCheckPtr = &heapCheck;
  insertCount = 0;
  minVal = false;
  maxVal = false;
}
template <class T> // Heap Destructor
MinMaxHeap<T>::Heap::~Heap() {
  delete [] m_array;
  delete [] m_arrayIndex;
  m_array = NULL;
  m_arrayIndex = NULL;
}
template <class T> // Sets the m_twin variable
void MinMaxHeap<T>::Heap::setTwin( Heap *twin ) { m_twin = twin; }
template <class T> // Returns the root of the heap
T MinMaxHeap<T>::Heap::getArrayPos( int pos ) { return m_array[ pos ]; }
template <class T> // Returns the position of the root value in twin
int MinMaxHeap<T>::Heap::getIndexPos( int pos ) { return m_arrayIndex[ pos ]; }
template <class T> //Returns the parent index of passed inde
int MinMaxHeap<T>::Heap::getParent( int index ) { return ( index / 2 ); }
template <class T> // Returns the left index of passed index
int MinMaxHeap<T>::Heap::getLeft( int index ) { return ( 2 * index ); }
template <class T> // Returns the right index of the passed index
int MinMaxHeap<T>::Heap::getRight( int index ) { return ( 2 * index + 1 ); }
template <class T> // inerts into the bottom-left most position
void MinMaxHeap<T>::Heap::insert( const T& data ) {
  if(m_size == m_capacity)
    throw overflow_error("insert: heap full");
  // Helps differ from Min and Max heaps
  if(m_twin->m_arrayIndex[0] == 0) {
    m_arrayIndex[0] = -1;
  }
  if(m_twin->m_arrayIndex[0] == -1) {
    m_arrayIndex[0] = -2;
  }
  // Increment Size and Put Data into last position
  m_size++;
  m_array [ m_size ] = data;
  m_twin->m_arrayIndex[ m_size ] = m_size;
}
template <class T> // Deletes the min or max
T MinMaxHeap<T>::Heap::deleteValue() {
  if(m_size == 0)
    throw overflow_error("delete: heap empty");

  int rootLocation = m_arrayIndex[1];
  T result = m_array[1];

  // Swap Values
  swap(m_size, 1);
  m_twin->swap(m_twin->m_size, rootLocation);
  // Decrement Sizes
  m_size--;
  m_twin->m_size--;
  //Fix heap
  bubbleDown();
  m_twin->bubbleUp();
  return result;
}
template <class T> // Bubbles up the Heap
void MinMaxHeap<T>::Heap::bubbleUp() {
  int child = m_size;
  int parent = getParent( child );
  // MIN
  if( m_arrayIndex[0] == -1 ) {
    while ( m_array [ child ] < m_array [ parent ]
	    && child > 0
	    && parent > 0 ) {
      swap ( child, parent );
      child = parent;
      parent = getParent ( child );
    }
  }
  // MAX
  if( m_arrayIndex[0] == -2 ) {
    while ( m_array [ child ] > m_array [ parent ]
            && child > 0
            && parent > 0 ) {
      swap ( child, parent );
      child = parent;
      parent = getParent ( child );
    }
  }
}
template <class T> // Bubbles down the Heap
void MinMaxHeap<T>::Heap::bubbleDown() {
  int parent = 1;
  bool loopControl = true;

  while ( loopControl ) {
    int left = getLeft( parent );
    int right = getRight( parent );
    int compare = parent;

    // MIN
    if( m_arrayIndex[0] == -1 ) {
      if ( left < m_size
	   && m_array [ left ] < m_array [ compare ] )
	compare = left;

      if ( right < m_size
	   && m_array [ right ] < m_array [ compare ] )
	compare = right;

      if(compare != parent) {
	swap(compare, parent);
	parent = compare;
      }
      else
	loopControl = false;
    }// MIN

    // MAX
    if( m_arrayIndex[0] == -2 ) {
      if ( left < m_size
           && m_array [ left ] > m_array [ compare ] )
        compare = left;

      if ( right < m_size
           && m_array [ right ] > m_array [ compare ] )
        compare = right;

      if(compare != parent) {
        swap(compare, parent);
        parent = compare;
      }
      else
        loopControl = false;
    }// MAX
  }// WHILE LOOP
}

template <class T> // Swaps two values
void MinMaxHeap<T>::Heap::swap( int child, int parent ) {
  T swapValue;
  int swapValueIndex;
  int tempChild = m_arrayIndex[child];
  int tempParent = m_arrayIndex[parent];

  //Swap m_array
  swapValue = m_array [ child ];
  m_array [ child ] = m_array [ parent ];
  m_array [ parent ] = swapValue;

  //Swap m_arrayIndex
  swapValueIndex = m_arrayIndex [ child ];
  m_arrayIndex [ child ] = m_arrayIndex [ parent ];
  m_arrayIndex [ parent ] = swapValueIndex;

  //Swap twin
  swapValueIndex = m_twin->m_arrayIndex [ tempChild ];
  m_twin->m_arrayIndex [ tempChild ] = m_twin->m_arrayIndex [ tempParent ];
  m_twin->m_arrayIndex [ tempParent ] = swapValueIndex;
}

template <class T> // returns size
int MinMaxHeap<T>::Heap::size() {
  return m_size;
}

template <class T> // Dumps heap
void MinMaxHeap<T>::Heap::dump() {
  cout << "size = " << m_size << ", ";
  cout << "capacity = " << m_capacity << endl;
  for ( int i = 1; i <= m_size; i++ )
    cout << "Heap[" << i << "] = (" << m_array [ i ]
	 << "," << m_arrayIndex[ i ] << ")\n";
}

/******************************************************
 ** HEAP AND MINMAXHEAP SEPARATOR
 *****************************************************/

template <class T> // MinMaxHeap Constructor
MinMaxHeap<T>::MinMaxHeap() {}

template <class T> // MinMaxHeap Overlaoded Constructor
MinMaxHeap<T>::MinMaxHeap( int capacity ) {
  m_capacity = capacity;
  m_size = 0;
  m_N = new Heap ( capacity );
  m_X = new Heap ( capacity );
  m_N->setTwin( m_X );
  m_X->setTwin( m_N );
}
template <class T> // MinmMaxHeap Copy Constructor
MinMaxHeap<T>::MinMaxHeap( const MinMaxHeap<T>& other) {
  m_capacity = other.m_capacity;
  m_size = other.m_N->m_size;
  m_N = new Heap ( other.m_capacity );
  m_X = new Heap ( other.m_capacity );
  m_N->setTwin( m_X );
  m_X->setTwin( m_N );
  m_N->m_size = other.m_N->m_size;
  m_X->m_size = other.m_N->m_size;

  for(int i = 0; i <= m_size; i++)
    m_N->m_array[i] = other.m_N->m_array[i];
  for(int i = 0; i <= m_size; i++)
    m_N->m_arrayIndex[i] = other.m_N->m_arrayIndex[i];
  for(int i = 0; i <= m_size; i++)
    m_X->m_array[i] = other.m_X->m_array[i];
  for(int i = 0; i <= m_size; i++)
    m_X->m_arrayIndex[i] = other.m_X->m_arrayIndex[i];
}
template <class T> // MinMaxHeap Destrucor
MinMaxHeap<T>::~MinMaxHeap() {
  delete m_N;
  delete m_X;
  m_N = NULL;
  m_X = NULL;
}
template <class T> // MinMaxHeap Overloaded Assignment Operator
const MinMaxHeap<T>& MinMaxHeap<T>::operator=( const MinMaxHeap<T>& rhs) {
  if(m_N)
    delete m_N;
  if(m_X)
    delete m_X;

  m_capacity = rhs.m_capacity;
  m_size = rhs.m_N->m_size;
  m_N = new Heap ( rhs.m_capacity );
  m_X = new Heap ( rhs.m_capacity );
  m_N->setTwin( m_X );
  m_X->setTwin( m_N );
  m_N->m_size = rhs.m_N->m_size;
  m_X->m_size = rhs.m_N->m_size;

  for(int i = 0; i <= m_size; i++)
    m_N->m_array[i] = rhs.m_N->m_array[i];
  for(int i = 0; i <= m_size; i++)
    m_N->m_arrayIndex[i] = rhs.m_N->m_arrayIndex[i];
  for(int i = 0; i <= m_size; i++)
    m_X->m_array[i] = rhs.m_X->m_array[i];
  for(int i = 0; i <= m_size; i++)
    m_X->m_arrayIndex[i] = rhs.m_X->m_arrayIndex[i];
  return *this;
}
template <class T> // Returns size
int MinMaxHeap<T>::size() { return m_N->size(); }
template <class T> // Inserts data into MinMax Heap
void MinMaxHeap<T>::insert( const T& data) {
  m_N->insert( data );
  m_X->insert( data );
  m_N->bubbleUp();
  m_X->bubbleUp();
}
template <class T> // Deletes the minimum value and it's twin
T MinMaxHeap<T>::deleteMin() { return m_N->deleteValue(); }
template <class T> // Deletes the maximum value and it's twin
T MinMaxHeap<T>::deleteMax() { return m_X->deleteValue(); }
template <class T> // Prints all Heap data to screen
void MinMaxHeap<T>::dump() {
  cout << "... MinMaxHeap::dump() ...\n\n";
  cout << "------------Min Heap------------\n";
  m_N->dump();
  cout << "------------Max Heap------------\n";
  m_X->dump();
}
template <class T> // Grading Function?
void MinMaxHeap<T>::locateMin( int pos, T& data, int& index ) {
  data = m_N->getArrayPos( pos );
  index = m_N->getIndexPos( pos );
}
template <class T> // Grading Function?
void MinMaxHeap<T>::locateMax( int pos, T& data, int& index ) {
  data = m_X->getArrayPos( pos );
  index = m_X->getIndexPos( pos );
}

#endif
