/**************************************************
 **
 ** Project 2: Square Lists, Round 2
 ** Version: 0.0.1
 ** File: DNode.cpp
 **
 ** Nicholas J Long
 ** CMSC 341, Section 01, John Park
 ** UMBC Spring 2018
 ** nlong2@umbc.edu
 **
 *************************************************/

#include "DNode.h"

DNode::DNode() {
  m_debug = false;

  if(m_debug)
    cout << "DNode Default Constructor.\n";

  m_next = NULL;
}
DNode::DNode(Int341 data) {
  if(m_debug)
    cout << "DNode Overloaded Constructor.\n";

  m_data = data;
  m_next = NULL;
}



