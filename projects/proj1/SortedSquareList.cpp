#include "SortedSquareList.h"
#include <iostream>
#include <cmath>

using namespace std;

// default constructor
SortedSquareList::SortedSquareList() {
  m_cols = new SSLColumn*[2];
  for(int i = 0; i < 2; i++) {
    m_cols[i] = new SSLColumn;
  }
  m_colInfo = new int[2];
  m_capacity = 2;
  m_size = 0;
  m_start = 0;
  m_end = 0;
  m_squareDimension = 2;
}
// copy constructor
SortedSquareList::SortedSquareList(const SortedSquareList& other) {
  m_cols = new SSLColumn*[other.m_squareDimension];

  for(int i = 0; i < m_squareDimension;i++)
    m_cols[i] = new SSLColumn(m_squareDimension);

  for(int i = 0; i < other.m_size; i++)
    *m_cols[i] = *other.m_cols[i];

  m_capacity = other.m_capacity;
  m_size = other.m_size;
  m_start = other.m_start;
  m_end = other.m_end;
  m_squareDimension = other.m_squareDimension;
}
// destructor
SortedSquareList::~SortedSquareList() {
  for(int i = 0 ; i < m_capacity;i++)
    delete m_cols[i];
  delete m_cols;
}
// overloaded assignment operator
// We can copy into differently-sized square list, as long as it is large
// enough to hold all of the actual stored data.
const SortedSquareList& SortedSquareList::operator=(const SortedSquareList& rhs) {
  if(m_capacity < rhs.m_capacity)
    m_capacity = rhs.m_capacity;

  if(m_cols)
    delete [] m_cols;

  //  m_cols = new SSLColumn[m_capacity];

  //  for(int i = 0; i < rhs.m_size; i++)


  m_size = rhs.m_size;
  m_start = rhs.m_start;
  m_end = (rhs.m_start + rhs.m_size) % m_capacity;

  return *this;
}
// Adds item to correct position in square list, based on sort order.
// Must grow dynamically allocated structures if we run out of room;
// REQUIREMENT: must execute in O(sqrt(n)) time, where n is
// number of items currently stored.
void SortedSquareList::add(int data) {
  resize(true);
  int column = -1;
  int index = 0;
  int temp = 0;

  for(int i = 0; i < m_size;i++) {
    if(m_cols[i]->size() != m_cols[i]->capacity())
      temp++;
  }
  if(m_size == 0)
    column = m_start;
  else if(size() % m_squareDimension == 0) {
    if(temp == 0)
      column = m_size++;
    else
      column = minusOne(m_end);
  }
  else if(m_cols[minusOne(m_end)]->findAt(-1) < data) {
    column = minusOne(m_end);
  }
  else {
    while(column == -1) {
      if(m_cols[index]->findAt(-1) >= data)
	  column = index;

      if(m_cols[index]->findAt(-1) < data)
	if(m_cols[index + 1]->findAt(0) > data)
	  if(m_cols[index]->size() != m_cols[index]->capacity())
	    column = index;

      index++;
    }
  }
  if((m_cols[column]->size() + 1) > m_squareDimension)
    shift(column, true, 0);

  m_cols[column]->add(data);

  int sizeCounter = 0;
  for(int i = 0; i < m_capacity; i++)
    if(m_cols[i]->size() > 0)
      sizeCounter++;
  m_size = sizeCounter;

  m_end = m_size % m_capacity;
  m_squareDimension = ceil(sqrt(size()));
  if(m_squareDimension < 2)
    m_squareDimension = 2;

}

int SortedSquareList::shift(int column, bool shiftType, int recursiveSwitch) {
  int result = 0;

  if(shiftType) {
    if(recursiveSwitch == 1) {
      result = m_cols[column]->removeFirst();
      if((m_cols[minusOne(column)]->size() + 1) > m_squareDimension)
	shift(minusOne(column), true, 1);
      m_cols[minusOne(column)]->add(result);
    }// if
    else if(recursiveSwitch == 2) {
      result = m_cols[column]->removeLast();
      if((m_cols[column + 1]->size() + 1) > m_squareDimension)
	shift(column + 1, true, 2);
      m_cols[column + 1]->add(result);
    }// else if
    else {
      if(column == m_end || column == m_start) {
	if(column == m_start) {
	  result = m_cols[column]->removeLast();
	  if((m_cols[column + 1]->size() + 1) > m_squareDimension)
	    shift(column + 1, true, 2);
	  m_cols[column + 1]->add(result);
	}
	else {
	  result = m_cols[column]->removeFirst();
	  if((m_cols[minusOne(column)]->size() + 1) > m_squareDimension)
	    shift(minusOne(column), true, 1);
	  m_cols[minusOne(column)]->add(result);
	}
      }
      else {
	bool shiftDirection = calculateMeanLengths(column);
	if(!shiftDirection) {
	  result = m_cols[column]->removeLast();
	  if((m_cols[column + 1]->size() + 1) > m_squareDimension)
	    shift(column + 1, true, 2);
	  m_cols[column + 1]->add(result);
	}
	else {
	  result = m_cols[column]->removeFirst();
	  if((m_cols[minusOne(column)]->size() + 1) > m_squareDimension)
	    shift(minusOne(column), true, 1);
	  m_cols[minusOne(column)]->add(result);
	}
      }
    }

    int sizeCounter = 0;
    for(int i = 0; i < m_capacity; i++)
      if(m_cols[i]->size() > 0)
	sizeCounter++;
    m_size = sizeCounter;
    m_end = m_size % m_capacity;
    m_squareDimension = ceil(sqrt(size()));
    if(m_squareDimension < 2)
      m_squareDimension = 2;
  }
  else {
    if(recursiveSwitch == 1) {
      result = m_cols[(column + 1) % m_capacity]->removeFirst();

      if((m_cols[(column + 1) % m_capacity]->size() - 1) < (m_squareDimension - 1))
	shift(column + 1, false, 1);

      m_cols[column]->add(result);
    }// if
    else if(recursiveSwitch == 2) {
      result = m_cols[minusOne(column)]->removeLast();

      if((m_cols[minusOne(column)]->size() - 1) < (m_squareDimension - 1))
	shift(minusOne(column), false, 2);

      m_cols[column]->add(result);
    }
    else {
      if(m_cols[minusOne(column)]->size() == m_squareDimension
	 || m_cols[(column + 1) % m_capacity]->size() == m_squareDimension) {
	if(m_cols[(column + 1) % m_capacity]->size() == m_squareDimension) {

	  result = m_cols[(column + 1) % m_capacity]->removeFirst();
	  if((m_cols[(column + 1) % m_capacity]->size() - 1) < (m_squareDimension - 1))
	    shift(column + 1, false, 1);
	  m_cols[column]->add(result);
	}// if
	else {
	  result = m_cols[minusOne(column)]->removeLast();
	  if((m_cols[minusOne(column)]->size() - 1) < (m_squareDimension - 1))
            shift(minusOne(column), false, 2);
	  m_cols[column]->add(result);
	}// else
      }// if
      else if(m_cols[minusOne(column)]->size() < (m_squareDimension - 1)
	      || m_cols[(column + 1) % m_capacity]->size() < (m_squareDimension - 1)) {

	if(m_cols[(column + 1) % m_capacity]->size() < (m_squareDimension - 1)) {

	  result = m_cols[(column + 1) % m_capacity]->removeFirst();
          if((m_cols[(column + 1) % m_capacity]->size() - 1) < (m_squareDimension - 1))
            shift(column + 1, false, 1);
	  m_cols[column]->add(result);
	}
	else {

	  result = m_cols[minusOne(column)]->removeLast();
          if((m_cols[minusOne(column)]->size() - 1) < (m_squareDimension - 1))
            shift(minusOne(column), false, 2);
          m_cols[column]->add(result);
	}
      }// else if
      else if(column != m_end || column != m_start) {
	result = m_cols[(column + 1) % m_capacity]->removeFirst();
	if((m_cols[(column + 1) % m_capacity]->size() - 1) < (m_squareDimension - 1))
	  shift(column + 1, false, 1);
	m_cols[column]->add(result);
      }// else if
      else {
      }// else
    }// else
    int sizeCounter = 0;
    for(int i = 0; i < m_capacity; i++)
      if(m_cols[i]->size() > 0)
        sizeCounter++;
    m_size = sizeCounter;
    m_end = m_size % m_capacity;
    m_squareDimension = ceil(sqrt(size()));
    if(m_squareDimension < 2)
      m_squareDimension = 2;
  }// else
  return -1;
}// shift
// returns position of item in list, -1 if not found.
// REQUIREMENT: must execute in O(log(n)) time
int SortedSquareList::find(int data) {
  int column = -1;
  int index = 0;

  if(m_size == 0)
    column = m_start;
  else if(size() % m_squareDimension == 0 && m_cols[minusOne(m_end)]->findAt(-1) <= data) {
    column = m_size++;
  }
  else if(m_cols[minusOne(m_end)]->findAt(-1) < data) {
    column = minusOne(m_end);
  }
  else {
    while(column == -1) {
      if(m_cols[index]->findAt(-1) >= data)
        column = index;
      index++;
    }
  }

  //  int result =  m_cols[index]->find(data);

  //  return result;
  return -1;
}
// Retrieves value at index pos in square list, based on total sort order.
// Throws exception if pos beyond end
// REQUIREMENT: must execute in O(log(n)) time
int SortedSquareList::findAt(int pos) {
  return -1;
}
// Finds and removes item from square list.
// Returns true if data found, false otherwise.
// REQUIREMENT: must execute in O(sqrt(n)) time
bool SortedSquareList::remove(int data) {
  resize(false);
  int column = -1;
  int index = 0;

  if(m_size == 0)
    column = m_start;
  else if(size() % m_squareDimension == 0 && m_cols[minusOne(m_end)]->findAt(-1) <= data) {
    column = m_size++;
  }
  else if(m_cols[minusOne(m_end)]->findAt(-1) < data) {
    column = minusOne(m_end);
  }
  else {
    while(column == -1) {
      if(m_cols[index]->findAt(-1) >= data)
        column = index;
      index++;
    }
  }

  if((m_cols[column]->size() - 1) < (m_squareDimension - 1))
    shift(column, false, 0);


  int result =  m_cols[column]->remove(data);
  if(result == -1)
    return false;

  int sizeCounter = 0;
  for(int i = 0; i < m_capacity; i++)
    if(m_cols[i]->size() > 0)
      sizeCounter++;
  m_size = sizeCounter;

  m_end = m_size % m_capacity;
  m_squareDimension = ceil(sqrt(size()));
  if(m_squareDimension < 2)
    m_squareDimension = 2;

  return true;
}
// return maximum number of active items this square list can hold with
// current allocation
int SortedSquareList::capacity() {
  return ((m_cols[0]->capacity()) * m_capacity);
}
// Total number of items in the square list as a whole, across all columns.
int SortedSquareList::size() {
  int total = 0;

  for(int i = 0; i < m_size; i++) {
    total = total + m_cols[(i + m_start) % m_capacity]->size();
  }
  return total;
}
// debugging function, prints out contents of data structure
void SortedSquareList::dump() {
  cout << "SortedSquareList::dump(): m_size =" << m_size << endl;

  for(int i = 0; i < m_size; i++) {
    cout << "[" << i << "]";
    m_cols[i]->dump();
  }
}
// Subtracts one from the integer given
// Keeps the number within the range of the capacity
int SortedSquareList::minusOne(int data) {
  data = (data - 1) % m_capacity;
  data = (data < 0) ? data + m_capacity : data;
  return data;
}

bool SortedSquareList::calculateMeanLengths(int column) {
  int leftMeanLength = 0;
  int leftTotal = 0;
  int leftDivisor = 0;
  int rightMeanLength = 0;
  int rightTotal = 0;
  int rightDivisor = 0;
  bool shiftDirection = 0;

  for(int i = 0; i < column; i++) {
    leftTotal = leftTotal + m_cols[i]->size();
    leftDivisor++;
  }

  if(leftDivisor == 0)
    leftMeanLength = 0;
  else
    leftMeanLength = leftTotal / leftDivisor;

  for(int i = (m_size - 1); i > column; i--) {
    rightTotal = rightTotal + m_cols[i]->size();
    rightDivisor++;
  }

  if(rightDivisor == 0)
    rightMeanLength = 0;
  else
    rightMeanLength = rightTotal / rightDivisor;

  if(leftMeanLength < rightMeanLength)
    shiftDirection = true;
  if(leftMeanLength > rightMeanLength)
    shiftDirection = false;
  if(rightMeanLength == 0 && size() % m_squareDimension > 0)
    shiftDirection = true;
  if(rightMeanLength == 0 && size() % m_squareDimension == 0)
    shiftDirection = false;

  if(rightTotal == leftTotal)
    shiftDirection = true;

  return shiftDirection;
}

void SortedSquareList::resize(bool add) {
  int tempSD = m_squareDimension;

  if(m_size != 0) {
    if(add)
      m_squareDimension = ceil(sqrt((size() + 1)));
    else
      m_squareDimension = ceil(sqrt((size() - 1)));
  }

  SSLColumn **tempCols;
  if(tempSD != m_squareDimension) {

    tempCols = new SSLColumn*[m_squareDimension];

    for(int i = 0; i < m_squareDimension; i++)
      tempCols[i] = new SSLColumn(m_squareDimension);
    for(int i = 0; i < m_size; i++)
      *tempCols[i] = *m_cols[i];
 
    for(int i = 0 ; i < m_capacity;i++)
      delete m_cols[i];
    delete m_cols;

    m_cols = new SSLColumn*[m_squareDimension];

    for(int i = 0; i < m_squareDimension; i++) {
      m_cols[i] = new SSLColumn(m_squareDimension);
      *m_cols[i] = *tempCols[i];
      delete tempCols[i];
    }
    delete tempCols;
    m_capacity = m_squareDimension;
    m_end = m_squareDimension - 1;
  }
}


