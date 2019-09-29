/**************************************************
 **
 ** Project 2: Square Lists, Round 2
 ** Version: 0.0.1
 ** File: INode.h
 **
 ** Nicholas J Long
 ** CMSC 341, Section 01, John Park
 ** UMBC Spring 2018
 ** nlong2@umbc.edu
 **
 *************************************************/
#ifndef _INODE_H_
#define _INODE_H_

#include "DNode.h"

class INode {
 public:
  INode();
  INode(DNode *dNode);
  DNode* getDNode();
  void setDNode(DNode *dNode);
  int getSize();
  void setSize(int size);
  void incrementSize();
  void decrementSize();
  void dump();
  DNode *m_dNode;
 private:
  //  DNode *m_dNode;
  int m_size;
  bool m_debug;
};
#endif
