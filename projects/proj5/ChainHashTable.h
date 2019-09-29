#ifndef CHAINHASHTABLE_H
#define CHAINHASHTABLE_H

#include "HashTable.h"
#include <iostream>
#include <list>

template <typename T>
class ChainHashTable: public HashTable<T> {
 public:
  ChainHashTable();
  ChainHashTable(unsigned int (*hashFunc)(const T&), int n=101);
  virtual ~ChainHashTable();
  ChainHashTable(ChainHashTable& other);
  const ChainHashTable& operator= (ChainHashTable& rhs);

  // Functions in a standard hash table interface,
  // independent of implementation:
  virtual bool insert(const T &data);
  virtual bool find(const T &data);
  virtual T remove(const T &data, bool &found);

  // Functions for debugging and grading:
  virtual void dump();
  virtual int at(int index, std::vector<T> &contents);

  int m_capacity;
  std::list<T> *m_table;
};
#include "ChainHashTable.cpp"
#endif
