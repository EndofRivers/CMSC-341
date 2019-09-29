/**************************************************
 **
 ** Project 2: Square Lists, Round 2
 ** Version: 0.1.1
 ** File: SqList.cpp
 **
 ** Nicholas J Long
 ** CMSC 341, Section 01, John Park
 ** UMBC Spring 2018
 ** nlong2@umbc.edu
 **
 ** FIX REMOVING LAST ELEMENT
 **
 *************************************************/
#include "SqList.h"
#include <cmath>
SqList::SqList() {
  m_debug = false;
  if(m_debug)
    cout << "SqList::Constructor\n";
  INode INode;
  m_iList.push_back(INode);
  m_numberOfItems = 0;
}
SqList::SqList(const SqList& other) {
  if(m_debug)
    cout << "SqList::Overloaded Constructor\n";
  m_iList = other.m_iList;
  m_numberOfItems = other.m_numberOfItems;
}
const SqList& SqList::operator=(const SqList& rhs) {
  if(m_debug)
    cout << "SqList::operator=\n";
  m_numberOfItems = rhs.m_numberOfItems;
  m_iList = rhs.m_iList;
  return *this;
}
SqList::~SqList() {
  if(m_debug)
    cout << "SqList::Destructor\n";
  DNode *remove, *curr = m_iList.begin()->getDNode();
  while(curr->m_next != NULL) {
    remove = curr;
    curr = curr->m_next;
    delete remove;
  }
}
void SqList::consolidate() {
  if(m_debug)
    cout << "SqList::consolidate\n";
  list<INode>::iterator it, itNext;
  int control = 0;
  for(it = m_iList.begin(); it != m_iList.end(); ++it) {
    itNext = it;
    itNext++;
    if(itNext == m_iList.end())
      control = 1;
    int size = it->getSize();
    int nextSize = itNext->getSize();
    int tooLong = (2*sqrt(m_numberOfItems));
    int tooShort = (sqrt(m_numberOfItems) / 2);
    DNode *temp = it->m_dNode;

    if(size == 0) {
      it = m_iList.erase(it);
    }
    else if(size <= tooShort && nextSize <= tooShort) {
      if(control != 1) {
	it->setSize((size + nextSize));
	m_iList.erase(itNext);
      }
    }    
    else if(size >= tooLong) {
      INode INode; // CREATE INODE
      int sizeCounter = 0; // SIZE COUNTER
      for(int i = 0; i < (size / 2); i++) {
	temp = temp->m_next;
	sizeCounter++;
      }
      it->setSize(sizeCounter); // SETS SIZE FOR OLD INODE
      sizeCounter = size - sizeCounter; // CREATES SIZE FOR INODE
      INode.setSize(sizeCounter);// SETS SIZE FOR INODE
      INode.setDNode(temp); // POINTSINODE TO THE CORRECT DNODE
      it++;
      m_iList.insert(it, INode); // INSERT INTO LIST
      it--;
    }
    else{}
  }
}
void SqList::insertEnd(const Int341& data, DNode* dNode) {
  DNode *Node = new DNode();
  Node->m_data = data;
  dNode->m_next = Node;
  Node->m_next = NULL;
}
void SqList::insertMiddle(const Int341& data, DNode* dNode) {
  DNode *Node = new DNode();
  Node->m_data = data;
  Node->m_next = dNode->m_next;
  dNode->m_next = Node;
}
void SqList::add(const Int341& data) {
  if(m_debug)
    cout << "SqList::add\n";
  list<INode>::iterator itTemp, it = m_iList.begin(); // LIST ITERATOR
  DNode *head, *tail, *curr;
  int control = 0;
  if(m_numberOfItems != 0) {
    for(itTemp = m_iList.begin(); itTemp != m_iList.end() && control == 0; itTemp++) {
      if(itTemp->getDNode()->m_data > data) {
	if(control == 0)
	  it = itTemp;
	if(it != m_iList.begin())
	  it--;
	control = 1;
      }
      if(itTemp->getDNode()->m_data <= data)
	it = itTemp;
    }
    head = it->getDNode();
    tail = it->getDNode();
    curr = it->getDNode();
    while(tail->m_next != NULL)
      tail = tail->m_next;
  }
  // EMPTY LIST
  if(m_numberOfItems == 0) {
    DNode *Node = new DNode();
    Node->m_data = data;
    m_iList.begin()->setDNode(Node);
  }
  // INSERT BEGIN
  else if(head->m_data > data) {
    DNode *Node = new DNode();
    Node->m_data = data;
    Node->m_next = it->m_dNode;
    it->setDNode(Node);
  }
  // INSERT END
  else if(tail->m_data <= data)
    insertEnd(data, tail);
  // INSERT MIDDLE
  else {
    int temp = 0;
    while(temp == 0) {
      if(curr->m_data <= data)
	if(curr->m_next->m_data > data)
	  temp = 1;
      if(temp == 0)
	curr = curr->m_next;
    }
    insertMiddle(data, curr);
  }
  it->incrementSize();
  m_numberOfItems++;
  consolidate();
}
Int341 SqList::remove(const Int341& data) {
  if(m_debug)
    cout << "SqList::remove\n";
  list<INode>::iterator itTemp, it = m_iList.begin(); // LIST ITERATOR
  DNode *prev, *curr, *remove;
  int control = 0;
  // FINDING THE RIGHT COLUMN
  // WILL GO ONE COLUMN BEHIND THE "RIGHT" COLUMN
  // WILL STOP AT m_iList.begin()
  for(itTemp = m_iList.begin(); itTemp != m_iList.end() && control == 0; itTemp++) {
    if(itTemp->getDNode()->m_data > data) {
      if(control == 0) {
	it = itTemp;
	if(it != m_iList.begin()) {
	  it--;
	  if(it != m_iList.begin())
	    it--;
	}// if
	control = 1;
      }// if control = 0
    }// if
    if(itTemp->getDNode()->m_data <= data)
      it = itTemp;
  }// for

  // REMOVE START OF LIST
  if(it->getDNode()->m_data == data) {
    curr = it->getDNode();
    it->setDNode(curr->m_next);
    Int341 result = curr->m_data;
    delete curr;
    it->decrementSize();
    m_numberOfItems--;
    consolidate();
    return result;
  }// if
  else {
    curr = it->getDNode();
    it++;
    if(it == m_iList.end()) {
      it--;
      DNode *tail = curr;
      while(tail->m_next != NULL) {
	curr = tail;
	tail = tail->m_next;	
	if(tail->m_data == data) {
	  if(tail->m_next == NULL) {
	    Int341 result = tail->m_data;
	    delete tail;
	    curr->m_next = NULL;
	    it->decrementSize();
	    m_numberOfItems--;
	    consolidate();
	    return result;
	  }
	  else {
	    remove = tail;
	    tail = tail->m_next;
	    curr->m_next = tail;
	    Int341 result = remove->m_data;
	    delete remove;
	    it->decrementSize();
	    m_numberOfItems--;
	    consolidate();
	    return result;
	  }
	}// if
      }// while
    }// if it = end
    it--;
    while(curr->m_next != NULL) {
      prev = curr;
      curr = curr->m_next;
      if(curr->m_data == data) {
	it++;
	remove = curr;
	curr = curr->m_next;
	prev->m_next = curr;
	Int341 result = remove->m_data;
	delete remove;
	it->decrementSize();
	m_numberOfItems--;
	consolidate();
	return result;
      }//if
    }// while
  }
  return NULL;
}
Int341 SqList::removeAt(int pos) {
  if(m_debug)
    cout << "SqList::removeAt\n";
  list<INode>::iterator itTemp, it = m_iList.begin(); // LIST ITERATOR
  DNode *prev, *curr, *remove; // DNode pointers
  int control = 0; // loop control
  int posCount = pos; // used to help find how many times needed to loop
  int size = 0;
  while(control == 0) {
    size = it->getSize();
    posCount = posCount - size;
    if(posCount < 0) {
      control = 1;
      posCount = posCount + size;
    }// if
    else
      it++;
  }// while
  if(posCount == 0) {
    if(it == m_iList.begin()) {
      // REMOVE THE FIRST ELEMENT IN ENTIRE LIST
      curr = it->getDNode();
      it->setDNode(curr->m_next);
      Int341 result = curr->m_data;
      delete curr;
      it->decrementSize();
      m_numberOfItems--;
      consolidate();
      return result;
    }
    else {
      // STEP BACK A COLUMN TO GET THE PREV FROM DESIRED REMOVE
      // HANDLE SPECIAL CASE HERE
      it--;
      posCount = posCount + it->getSize();
      curr = it->getDNode();
      while(posCount > 0) {
	prev = curr;
	curr = curr->m_next;
	posCount--;
      }
      it++;
      remove = curr;
      curr = curr->m_next;
      prev->m_next = curr;
      it->setDNode(curr);
      Int341 result = remove->m_data;
      delete remove;
      it->decrementSize();
      m_numberOfItems--;
      consolidate();
      return result;
    }
  }
  curr = it->getDNode();
  while(posCount > 0) {
    prev = curr;
    curr = curr->m_next;
    posCount--;
  }
  if(curr->m_next == NULL) {
    Int341 result = curr->m_data;
    delete curr;
    prev->m_next = NULL;
    it->decrementSize();
    m_numberOfItems--;
    consolidate();
    return result;
  }
  else {
    remove = curr;
    curr = curr->m_next;
    prev->m_next = curr;
    Int341 result = remove->m_data;
    delete remove;
    it->decrementSize();
    m_numberOfItems--;
    consolidate();
    return result;
  }
  return NULL;
}
Int341& SqList::operator[](int pos) {
  if(m_debug)
    cout << "SqList::operator[]\n";
  list<INode>::iterator itTemp, it = m_iList.begin(); // LIST ITERATOR
  DNode *curr; // DNode pointer
  int control = 0; // loop control
  int posCount = pos; // used to help find how many times needed to loop
  int size = 0;
  while(control == 0) {
    size = it->getSize();
    posCount = posCount - size;
    if(posCount < 0) {
      control = 1;
      posCount = posCount + size;
    }// if
    else
      it++;
  }// while

  curr = it->getDNode();
  while(posCount > 0) {
    curr = curr->m_next;
    posCount--;
  }
  return curr->m_data;
}
int SqList::indexOf(const Int341& data) {
  if(m_debug)
    cout << "SqList::indexOf\n";
  list<INode>::iterator itTemp, it = m_iList.begin(); // LIST ITERATOR
  DNode *curr;
  int control = 0;
  int posCount = 0;
  int posTotal = 0;
  for(itTemp = m_iList.begin(); itTemp != m_iList.end() && control == 0; itTemp++) {
    // Running total of elements
    posCount = posCount + itTemp->getSize();
    posTotal = posCount;
    //
    if(itTemp->getDNode()->m_data > data) {
      if(control == 0) {
	posCount = posCount - itTemp->getSize();
        if(itTemp != m_iList.begin()) {
	  itTemp--;
	  posCount = posCount - itTemp->getSize();
	  //	  itTemp--;
        }// if
        control = 1;
      }// if control = 0
    }// if
    if(control == 1)
      it = itTemp;
    if(itTemp->getDNode()->m_data <= data) {
      it = itTemp;
    }
  }// for

  // Check for end of list
  if(it->getDNode()->m_data <= data)
    posCount = posCount - it->getSize();

  // Set current node and iterate up to data
  curr = it->getDNode();
  while(posCount <= posTotal) {
    if(curr->m_data == data)
      return posCount;
    else
      posCount++;
    curr = curr->m_next;
  }
  //Return -1 if nothing found
  return -1;
}
int SqList::numItems() {
  if(m_debug)
    cout << "SqList::numItems\n";
  return m_numberOfItems;
}
void SqList::dump() {
  cout << "----- SqList dump() -----\n";
  cout << "number of items = " << m_numberOfItems << endl;
  cout << "-------------------------\n";
  list<INode>::iterator it; // LIST ITERATOR
  int column = 0; // COLUMN COUNTER
  // LOOP FROM THE START TO THE END OF THE LIST
  for(it = m_iList.begin(); it != m_iList.end(); it++) {
    cout << column << " (" << it->getSize() << ") : ";
    it->dump(); // ENTER INODE'S DUMP
    cout << endl;
    column++;
  }
}

