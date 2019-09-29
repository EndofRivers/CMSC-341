#ifndef _PROBEHASHTABLE_CPP_
#define _PROBEHASHTABLE_CPP_

#include "ProbeHashTable.h"

template<typename T>
ProbeHashTable<T>::HashTableEntry::HashTableEntry() {
  m_flag = Empty;
}
template<typename T>
ProbeHashTable<T>::HashTableEntry::~HashTableEntry() {

}
template<typename T>
ProbeHashTable<T>::ProbeHashTable() {}
template <typename T>
ProbeHashTable<T>::ProbeHashTable(unsigned int (*hashFunc)(const T&), int n) {
  m_capacity = n;
  m_table = new HashTableEntry[m_capacity];
  this->hashFunc = hashFunc;
}
template <typename T>
ProbeHashTable<T>::~ProbeHashTable() {
  delete [] m_table;
}
template <typename T>
ProbeHashTable<T>::ProbeHashTable (ProbeHashTable& other) {
  m_capacity = other.m_capacity;
  this->hashFunc = other.hashFunc;
  m_table = new HashTableEntry[m_capacity];
  for(int i = 0; i < m_capacity; i++) {
    m_table[i].m_data = other.m_table[i].m_data;
    m_table[i].m_flag = other.m_table[i].m_flag;
  }
}
template <typename T>
const ProbeHashTable<T>& ProbeHashTable<T>::operator= (ProbeHashTable& rhs) {
  if(m_table)
    delete [] m_table;
  m_capacity = rhs.m_capacity;
  this->hashFunc = rhs.hashFunc;
  m_table = new HashTableEntry[m_capacity];
  for(int i = 0; i < m_capacity; i++) {
    m_table[i].m_data = rhs.m_table[i].m_data;
    m_table[i].m_flag = rhs.m_table[i].m_flag;
  }
  return *this;
}
// Functions in a standard hash table interface,
// independent of implementation:
template <typename T>
bool ProbeHashTable<T>::insert(const T &data) {
  int index = (hashFunc(data) % m_capacity);
  bool inserted = false;
  if(sizeof(m_table) == m_capacity)
    throw std::overflow_error("Hash Table Full");

  while(!inserted) {
    if(m_table[index].m_flag == Empty || m_table[index].m_flag == Deleted) {
      m_table[index].m_data = data;
      m_table[index].m_flag = Full;
      return true;
    }
    if(m_table[index].m_flag == Full) {
      if(m_table[index].m_data == data)
	return false;
      else {
	index++;
	index %= m_capacity;
      }
    }
  }
  return false;
}
template <typename T>
bool ProbeHashTable<T>::find(const T &data) {
  int index = (hashFunc(data) % m_capacity);
  bool found = false;
  int count = 0;

  while(!found || count == m_capacity) {
    count++;
    if(m_table[index].m_flag == Empty)
      return false;
    else {
      if(m_table[index].m_data == data) {
	found = true;
	return true;
      }
      else
	index++;
    }
  }
  return false;
}
template <typename T>
T ProbeHashTable<T>::remove(const T &data, bool &found) {
  int index = (hashFunc(data) % m_capacity);
  bool removed = false;
  int count = 0;

  while(!removed || count == m_capacity) {
    count++;
    if(m_table[index].m_flag == Empty) {
      found = false;
      return data;
    }
    else {
      if(m_table[index].m_data == data) {
        found = true;
	m_table[index].m_flag = Deleted;
        return m_table[index].m_data;
      }
      else
        index++;
    }
  }
  return data;
}
// Functions for debugging and grading:
template <typename T>
void ProbeHashTable<T>::dump() {
  std::cout << "ProbeHashTable dump; size: " << m_capacity << " buckets\n";
  for(int i = 0; i < m_capacity; i++) {
    std::cout << "[" << i << "]: ";
    if(m_table[i].m_flag == Empty)
      std::cout << "EMPTY";
    else if(m_table[i].m_flag == Deleted)
      std::cout << "DELETED";
    else 
      std::cout << m_table[i].m_data << "(" 
		<< (hashFunc(m_table[i].m_data) % m_capacity) << ")";
    std::cout << "\n";
  } // for
}
template <typename T>
int ProbeHashTable<T>::at(int index, std::vector<T> &contents) {
  if(m_table[index].m_flag == Full) {
    contents.push_back(m_table[index].m_data);
    return 1;
  }
  else
    return 0;
}

#endif



