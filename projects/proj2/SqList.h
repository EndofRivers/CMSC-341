/**************************************************
 **
 ** Project 2: Square Lists, Round 2
 ** Version: 0.0.1
 ** File: SqList.h
 **
 ** Nicholas J Long
 ** CMSC 341, Section 01, John Park
 ** UMBC Spring 2018
 ** nlong2@umbc.edu
 **
 *************************************************/
#ifndef _SQLIST_H_
#define _SQLIST_H_

#include "INode.h"
#include <list>

class SqList {
 public:
  SqList();
  SqList(const SqList& other);
  const SqList& operator=(const SqList& rhs);
  ~SqList();
  void consolidate();
  void insertEnd(const Int341& data, DNode* dNode);
  void insertMiddle(const Int341& data, DNode* dNode);
  void add(const Int341& data);
  Int341 remove(const Int341& data);
  Int341 removeAt(int pos);
  Int341& operator[](int pos);
  int indexOf(const Int341& data);
  int numItems();
  void dump();
  void inspector();
 private:
  bool m_debug; // TRUE: Prints debug statements, FALSE: No debug statements
  int m_numberOfItems; // Holds the total number of items in the SqList
  list<INode> m_iList; // Creates the "columns"
};
#endif
