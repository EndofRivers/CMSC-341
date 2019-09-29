/**************************************************
 **
 ** Project 2: Square Lists, Round 2
 ** Version: 0.0.1
 ** File: DNode.h
 **
 ** Nicholas J Long
 ** CMSC 341, Section 01, John Park
 ** UMBC Spring 2018
 ** nlong2@umbc.edu
 **
 *************************************************/
#ifndef _DNODE_H_
#define _DNODE_H_

#include <iostream>
#include "Int341.h"

using namespace std;

class DNode {
 public:
  DNode();
  DNode(Int341 data);
  Int341 getData();
  void setData(Int341 data);
  DNode* getNext();
  void setNext(DNode *next);
  void dump();
  DNode *m_next;
  Int341 m_data;
 private:
  bool m_debug;
};
#endif
