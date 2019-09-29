#ifndef _CHAINHASHTABLE_CPP_
#define _CHAINHASHTABLE_CPP_

#include "ChainHashTable.h"
template<typename T>
ChainHashTable<T>::ChainHashTable() {}
template <typename T>
ChainHashTable<T>::ChainHashTable(unsigned int (*hashFunc)(const T&), int n) {
  m_capacity = n;
  m_table = new std::list<T>[m_capacity];
  this->hashFunc = hashFunc;
}
template <typename T>
ChainHashTable<T>::~ChainHashTable() {
  delete [] m_table;
}
template <typename T>
ChainHashTable<T>::ChainHashTable (ChainHashTable& other) {
  m_capacity = other.m_capacity;
  this->hashFunc = other.hashFunc;

  m_table = new std::list<T>[m_capacity];
  for(int i = 0; i < m_capacity; i++) {
    m_table[i] = other.m_table[i];
  }
}
template <typename T>
const ChainHashTable<T>& ChainHashTable<T>::operator= (ChainHashTable& rhs) {
  if(m_table)
    delete [] m_table;
  m_capacity = rhs.m_capacity;
  this->hashFunc = rhs.hashFunc;

  m_table = new std::list<T>[m_capacity];
  for(int i = 0; i < m_capacity; i++) {
    m_table[i] = rhs.m_table[i];
  }
  return *this;
}
// Functions in a standard hash table interface,
// independent of implementation:
template <typename T>
bool ChainHashTable<T>::insert(const T &data) {
  int index = (hashFunc(data) % m_capacity);
  bool dataExists = false;
  typename std::list<T>::iterator it;

  for(it = m_table[index].begin(); it != m_table[index].end(); ++it) {
    if(*it == data)
      dataExists = true;
  }
  if(!dataExists) {
    m_table[index].push_front(data);
    return true;
  }
  else
    return false;
}
template <typename T>
bool ChainHashTable<T>::find(const T &data) {
  int index = (hashFunc(data) % m_capacity);
  typename std::list<T>::iterator it;
  for(it = m_table[index].begin(); it != m_table[index].end(); ++it) {
    if(*it == data) {
      return true;
    }
  }
  return false;
}
template <typename T>
T ChainHashTable<T>::remove(const T &data, bool &found) {
  int index = (hashFunc(data) % m_capacity);
  typename std::list<T>::iterator it;
  for(it = m_table[index].begin(); it != m_table[index].end(); ++it) {
    if(*it == data) {
      m_table[index].erase(it);
      found = true;
      return *it;
    }
  }
  found = false;
  return data;
}
// Functions for debugging and grading:
template <typename T>
void ChainHashTable<T>::dump() {
  typename std::list<T>::iterator it;
  std::cout << "ChainHashTable dump; size: " << m_capacity << " buckets\n";

  for(int i = 0; i < m_capacity; i++) {
    std::cout << "[" << i << "]: ";
    if(!m_table[i].empty()) {
      for(it = m_table[i].begin(); it != m_table[i].end(); ++it) {
	std::cout << *it << ", ";
      } // for
    } // if
    std::cout << "\n";
  } // for
}
template <typename T>
int ChainHashTable<T>::at(int index, std::vector<T> &contents) {
  //contents.push_back(m_table[index].begin());
  return m_table[index].size();
}
#endif



