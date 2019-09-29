// Nick Long
// CMSC 341 Spring'18
// SSLColumn.cpp
// nlong2@umbc.edu

#include <iostream>
#include "SSLColumn.h"
#include <stdexcept>

using namespace std;

// Constructor, default size is 2
SSLColumn::SSLColumn(int n) {
  m_data = new int[n];
  m_capacity = n;
  m_size = 0;
  m_start = 0;
  m_end = 0;
}
// Copy constructor
// Makes exact copy, including relative positions in circular buffers
SSLColumn::SSLColumn(const SSLColumn& other) {
  m_data = new int[other.m_capacity];

  for(int i = 0; i < other.m_capacity; i++)
    m_data[i] = other.m_data[i];

  m_capacity = other.m_capacity;
  m_size = other.m_size;
  m_start = other.m_start;
  m_end = other.m_end;
} 
// Destructor
SSLColumn::~SSLColumn() {
  delete[] m_data;
}
// overloaded assignment operator
// We can copy into differently-sized array.  Copying done in-place if
// target has sufficient capacity; else, target's internal array
// will be reallocated to a larger size.
const SSLColumn& SSLColumn::operator=(const SSLColumn& rhs) {
  // change capacity if needed
  if(m_capacity < rhs.m_capacity)
    m_capacity = rhs.m_capacity;
  if(m_data)
    delete [] m_data;

  m_data = new int[m_capacity];

  for(int i = 0; i < rhs.m_size; i++)
    m_data[((i + rhs.m_start) % m_capacity)] = rhs.m_data[((i + rhs.m_start) % rhs.m_capacity)];

  m_size = rhs.m_size;
  m_start = rhs.m_start;
  m_end = (rhs.m_start + rhs.m_size) % m_capacity;
  return *this;
}
// Adds item to correct sorted order position in circular buffer.
// Throws exception if out of room.
// REQUIREMENT: must execute in O(n) time, where n is size of column
void SSLColumn::add(int data) {
  if(m_size == m_capacity)
    throw overflow_error("add: column full");

  if(m_size == 0) {
    //    cout << "SSLColumn add() IF" << endl;
    m_data[m_start] = data;
    m_size++;
    m_end = (m_end + 1) % m_capacity;
  }
  else if(m_data[m_start] >= data) {
    addFirst(data);
  }
  else if(data >= m_data[minusOne(m_end)]) {
    //    cout << "SSLColumn add() ELSE IF" << endl;
    m_data[m_end] = data;
    m_size++;
    m_end = (m_end + 1) % m_capacity;
    }
  else {
    //    cout << "SSLColumn add() ELSE" << endl;
    int temp = 0;
    int temp2 = -1;
    if(m_data[m_start] >= data)
      temp = 0;
    else
      for(int i = 0; i < m_size; i++)
	if(m_data[(i + m_start) % m_capacity] > data)
	  if(temp2 == -1) {
	    temp = ((i + m_start) % m_capacity);
	    temp2 = 1;
	  }
    
	if(temp > 0)
	  for(int j = m_size; j > temp; j--)
	    m_data[(j + 1) % m_capacity] = m_data[j % m_capacity];


	    //m_data[j % m_capacity] = m_data[minusOne(j)];


	if((m_size - temp) == 1) {
	  temp2 = m_data[temp];
	  m_data[m_size] = temp2;
	}


	if(temp == 0)
	  for(int i = m_end; i > temp; i--)
	    m_data[i % m_capacity] = m_data[minusOne(i)];

	if(m_size == temp)
	  m_data[(temp + 1) % m_capacity] = m_data[temp];
	
	m_data[temp] = data;
	m_size++;
	m_end = (m_end + 1) % m_capacity;
      
    if(m_size == m_capacity)
      m_end = m_start;
  }
}
// Adds item to top/left of circular buffer.
// Throws exception if out of room.
// REQUIREMENT: must execute in O(1) time
void SSLColumn::addFirst(int data) {
  if(m_size == m_capacity)
    throw overflow_error("addFirst: column full");
  if(m_size == 0) {
    m_data[m_start] = data;
    m_size++;
    m_end = (m_end + 1) % m_capacity;
  }
  else {
    m_data[minusOne(m_start)] = data;
    m_size++;
    m_start = minusOne(m_start);
  }
}
// Adds item to bottom/right of circular buffer.
// Throws exception if out of room.
// REQUIREMENT: must execute in O(1) time
void SSLColumn::addLast(int data) {
  if(m_size == m_capacity)
    throw overflow_error("addLast: column full");
  m_data[m_end] = data;
  m_size++;
  m_end = (m_end + 1) % m_capacity;
}
// returns position of item in column, -1 if not found.
// REQUIREMENT: must execute in O(log(n)) time, where n is size of column
int SSLColumn::find(int data) {
  int high = m_end + m_size;
  int low = m_start;
  int mid;

  while(low <= high) {
    mid = (low + (high - low) / 2) % m_capacity;

    if(m_data[mid] == data)
      return mid;

    if(m_data[mid] < data)
      low = mid + 1;
    else
      high = minusOne(mid);
  }
  return -1;
}
// Retrieves value at index pos in circular buffer, based on sort order.
// If pos == -1, retrieves last value in list, a la Python
// Throws exception if pos >= size.
// REQUIREMENT: must execute in O(1) time.
int SSLColumn::findAt(int pos) {
  if(pos >= m_size)
    throw out_of_range("findAt: bad position");
  else if(pos < -1)
    throw out_of_range("findAt: bad position");
  else if(pos == -1)
    return m_data[minusOne(m_end)];
  else {
    pos = (pos + m_start) % m_capacity;
    pos = (pos < 0) ? pos + m_capacity : pos;
    return m_data[pos];
  }
}
// Removes item from column, returning original position of item,
// -1 if not found.
// REQUIREMENT: must execute in O(n) time, where n is size of column
int SSLColumn::remove(int data) {
  int index = find(data);
  if(m_size == 0)
    return -1;
  else if(index == -1)
    return -1;
  else {
    m_data[index] = NULL;
    if(index == m_start)
      m_start = (m_start + 1) % m_capacity;
    else if(index == minusOne(m_end))
      m_end = minusOne(m_end);
    else {
      for(int i = index; i < m_size; i++)
	m_data[i % m_capacity] = m_data[(i + 1) % m_capacity];
      
      m_end = minusOne(m_end);
    }
    m_size--;
    return index;
  }
}
// Removes top/left item from circular buffer and returns it.
// Throws exception if empty
// REQUIREMENT: must execute in O(1) time
int SSLColumn::removeFirst(void) {
  if(m_size == 0)
    throw length_error("Empty Array");
  else {
    int temp = m_data[m_start];
    m_data[m_start] = NULL;
    m_start = (m_start + 1) % m_capacity;
    m_size--;
    return temp;
  }
}
// Removes bottom/right item from circular buffer and returns it.
// Throws exception if empty.
// REQUIREMENT: must execute in O(1) time
int SSLColumn::removeLast(void) {
  if(m_size == 0)
    throw length_error("Empty Array");
  else {

    int temp = m_data[minusOne(m_end)];
    m_data[minusOne(m_end)] = NULL;
    m_end = minusOne(m_end);
    m_size--;
    return temp;
  }
}
// return maximum number of items this buffer can hold
int SSLColumn::capacity() {return m_capacity;}
// return number of items currently held in the buffer
int SSLColumn::size() {return m_size;}
// debugging function. Prints out contents.
void SSLColumn::dump() {
  cout << "SSLColumn::dump(): m_size = " << m_size << endl;
  for(int i = 0; i < m_size; i++)
    cout << "[" << (i+ m_start)%m_capacity << "] " << m_data[((i + m_start) % m_capacity)] << ", ";
  cout << endl;
}
// Subtracts one from the integer given
// Keeps the number within the range of the capacity
int SSLColumn::minusOne(int data) {
  data = (data - 1) % m_capacity;
  data = (data < 0) ? data + m_capacity : data;
  return data;
}



