#ifndef PROBEHASHTABLE_H
#define PROBEHASHTABLE_H

#include "HashTable.h"
#include <iostream>
#include <stdexcept>

enum State {Deleted = -1, Empty = 0, Full = 1};

template <typename T>
class ProbeHashTable: public HashTable<T> {
 public:
  class HashTableEntry {
  public:
    HashTableEntry();
    virtual ~HashTableEntry();
    T m_data;
    int m_flag;
  };
  ProbeHashTable();
  ProbeHashTable(unsigned int (*hashFunc)(const T&), int n=101);
  virtual ~ProbeHashTable();
  ProbeHashTable(ProbeHashTable& other);
  const ProbeHashTable& operator= (ProbeHashTable& rhs);

  // Functions in a standard hash table interface,
  // independent of implementation:
  virtual bool insert(const T &data);
  virtual bool find(const T &data);
  virtual T remove(const T &data, bool &found);

  // Functions for debugging and grading:
  virtual void dump();
  virtual int at(int index, std::vector<T> &contents);

  int m_capacity;
  HashTableEntry *m_table;
};
#include "ProbeHashTable.cpp"
#endif
