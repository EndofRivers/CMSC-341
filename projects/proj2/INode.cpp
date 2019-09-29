/**************************************************
 **
 ** Project 2: Square Lists, Round 2
 ** Version: 0.0.1
 ** File: INode.cpp
 **
 ** Nicholas J Long
 ** CMSC 341, Section 01, John Park
 ** UMBC Spring 2018
 ** nlong2@umbc.edu
 **
 *************************************************/
#include "INode.h"

INode::INode() {
  m_debug = false;
  if(m_debug)
    cout << "INode Default Constructor.\n";
  m_size = 0;
  m_dNode = NULL;
}
INode::INode(DNode *dNode) {
  m_debug = false;
  if(m_debug)
    cout << "INode Overloaded Constructor.\n";

  m_size = 0;
  m_dNode = dNode;
}
DNode* INode::getDNode() {
  if(m_debug)
    cout << "INode::getDNode\n";

  return m_dNode;
}
void INode::setDNode(DNode *dNode) {
  m_dNode = dNode;
}
int INode::getSize() {

  return m_size;
}
void INode::setSize(int size) {
  m_size = size;
}
void INode::incrementSize() {
  if(m_debug)
    cout << "INode::incrementSize\n";
  m_size++;
}
void INode::decrementSize() {
  if(m_debug)
     cout << "INode::decrementSize\n";
  m_size--;
}
void INode::dump() {
  DNode *head, *curr, *next;
  head = m_dNode;
  next = head;
  for(int i = 0; i < m_size; i++) {
    curr = next;
    cout << curr->m_data.m_data << " ";
    next = curr->m_next;
  }
}
