#include "QTNode.h"
#include <cmath>
QTNode::iterator::iterator() {

}
bool QTNode::iterator::operator==(const QTNode::iterator &other) {

  return false;
}
bool QTNode::iterator::operator!=(const QTNode::iterator &other) {

  return false;
}
// Prefix:: e.g. "++it"
QTNode::iterator::iterator& QTNode::iterator::operator++() {

}
// Postfix: "it++"
QTNode::iterator::iterator QTNode::iterator::operator++(int dummy) {

}
QTNode*& QTNode::iterator::operator*() {

}
QTNode::QTNode() {
  m_bounds.m_dim = 1;
  m_data = NULL;
  topLeftTree = NULL;
  topRightTree = NULL;
  botLeftTree = NULL;
  botRightTree = NULL;
}
QTNode::~QTNode() {

}
bool QTNode::isLeaf() {
  if(topLeftTree == NULL
     && topRightTree == NULL
     && botLeftTree == NULL
     && botRightTree == NULL)
    return true;
  else
    return false;
}
void QTNode::findQuad(const Point &pt, int data, bool add) {
  bool empty = true;
  //Left
  if(m_bounds.m_bL.m_x >= pt.m_x) {
    //botLeftTree
    if(m_bounds.m_bL.m_y >= pt.m_y) {
      //Called from Add
      if(add) {
	if(botLeftTree == NULL)
	  botLeftTree = new QTNode();
	botLeftTree->add(pt, data);
      }
      //Called from Remove
      else {
	if(botLeftTree != NULL)
	  if(botLeftTree->remove(pt, empty))
	    botLeftTree = NULL;
      }
    }
    //topLeftTree
    else {
      //Called from Add
      if(add) {
	if(topLeftTree == NULL)
	  topLeftTree = new QTNode();
	topLeftTree->add(pt, data);
      }
      //Called from Remove
      else {
	if(topRightTree != NULL)
	  if(topRightTree->remove(pt, empty))
	    topRightTree = NULL;
      }
    }
  }
  //Right
  else {
    //botRightTree
    if(m_bounds.m_bL.m_y >= pt.m_y) {
      //Called from Add
      if(add) {
	if(botRightTree == NULL)
	  botRightTree = new QTNode();
	botRightTree->add(pt, data);
      }
      //Called from Remove
      else {
	if(botRightTree != NULL)
	  if(botRightTree->remove(pt, empty))
	    botRightTree = NULL;
      }
    }
    //topRightTree
    else {
      //Called from Add
      if(add) {
	if(topRightTree == NULL)
	  topRightTree = new QTNode();
	topRightTree->add(pt, data);
      }
      //Called from Remove
      else {
	if(topRightTree != NULL)
	  if(topRightTree->remove(pt, empty))
	    topRightTree = NULL;
      }
    }
  }
}
bool QTNode::add(const Point &pt, int data) {
  // CHILDLESS PARENT
  if(m_data != NULL && isLeaf()) {
    if(m_point == pt)
      if(m_data == data)
	return false;
      else {
	m_data = data;
	return true;
      }
    else {
      findQuad(m_point, m_data, true);
      m_data = NULL;
    }
  }// else if
  // LEAF NODE
  if(isLeaf()) {
    m_bounds.resize(m_point, pt);
    m_bounds.m_bL = pt;
    m_point = pt;
    m_data = data;
    return true;
  }// if
  else {
    findQuad(pt, data, true);
  }// else
}
bool QTNode::remove(const Point &pt, bool &empty) {
  if(isLeaf() && m_point == pt) {
    m_point = Point(NULL, NULL);
    m_data = NULL;
    m_bounds.m_bL = Point(NULL, NULL);
    m_bounds.m_dim = 1;
    return true;
  }
  else
    findQuad(pt, 0, false);

  int counter = 0;
  int singleKid = 0;
  if(botLeftTree != NULL) {
    counter++;
    singleKid = 1;
  }
  if(botRightTree != NULL) {
    counter++;
    singleKid = 2;
  }
  if(topLeftTree != NULL) {
    counter++;
    singleKid = 3;
  }
  if(topRightTree != NULL) {
    counter++;
    singleKid = 4;
  }

  if(counter == 1) {
    //botLeftTree
    if(singleKid == 1) {
      m_point = botLeftTree->m_point;
      m_data = botLeftTree->m_data;
      m_bounds.m_bL = botLeftTree->m_bounds.m_bL;
      m_bounds.m_dim = botLeftTree->m_bounds.m_dim;
      botLeftTree->m_point = Point(NULL, NULL);
      botLeftTree->m_data = NULL;
      botLeftTree->m_bounds.m_bL = Point(NULL, NULL);
      botLeftTree->m_bounds.m_dim = 1;
      botLeftTree = NULL;
    }
    //botRightTree
    if(singleKid == 2) {
      m_point = botRightTree->m_point;
      m_data = botRightTree->m_data;
      m_bounds.m_bL = botRightTree->m_bounds.m_bL;
      m_bounds.m_dim = botRightTree->m_bounds.m_dim;
      botRightTree->m_point = Point(NULL, NULL);
      botRightTree->m_data = NULL;
      botRightTree->m_bounds.m_bL = Point(NULL, NULL);
      botRightTree->m_bounds.m_dim = 1;
      botRightTree = NULL;
    }
    //topLeftTree
    if(singleKid == 3) {
      m_point = topLeftTree->m_point;
      m_data = topLeftTree->m_data;
      m_bounds.m_bL = topLeftTree->m_bounds.m_bL;
      m_bounds.m_dim = topLeftTree->m_bounds.m_dim;
      topLeftTree->m_point = Point(NULL, NULL);
      topLeftTree->m_data = NULL;
      topLeftTree->m_bounds.m_bL = Point(NULL, NULL);
      topLeftTree->m_bounds.m_dim = 1;
      topLeftTree = NULL;
    }
    //topRightTree
    if(singleKid == 4) {
      m_point = topRightTree->m_point;
      m_data = topRightTree->m_data;
      m_bounds.m_bL = topRightTree->m_bounds.m_bL;
      m_bounds.m_dim = topRightTree->m_bounds.m_dim;
      topRightTree->m_point = Point(NULL, NULL);
      topRightTree->m_data = NULL;
      topRightTree->m_bounds.m_bL = Point(NULL, NULL);
      topRightTree->m_bounds.m_dim = 1;
      topRightTree = NULL;
    }
  }
  return false;
}
bool QTNode::find(const Point &pt, int &data) {
  if(m_point == pt) {
    data = m_data;
    return true;
  }
  else {
    //Left
    if(m_bounds.m_bL.m_x >= pt.m_x) {
      //botLeftTree
      if(m_bounds.m_bL.m_y >= pt.m_y) {
	if(botLeftTree != NULL)
	  botLeftTree->find(pt,data);
      }
      //topLeftTree
      else {
	if(topLeftTree != NULL)
	  topLeftTree->find(pt,data);
      }
    }
    //Right
    else {
      //botRightTree
      if(m_bounds.m_bL.m_y >= pt.m_y) {
	if(botRightTree != NULL)
	  botRightTree->find(pt,data);
      }
      //topRightTree
      else {
	if(botRightTree != NULL)
	  topRightTree->find(pt,data);
      }
    }
  }
  return false;
}
int QTNode::findPoints(const BBox &region, std::vector<Point> &found) {

  return -1;
}
void QTNode::dump() {
  if(m_data == NULL && isLeaf()) {
    std::cout << "Empty Tree\n";
  }
  else {
    if(isLeaf()) {
      std::cout << "[QTNode bounds={botLeft=" << m_bounds.m_bL
		<< ", dim=" << m_bounds.m_dim << "} is LEAF: pt=" << m_point 
		<< ", data=" << m_data << "]\n";
    }
    else {
      std::cout << "[QTNode bounds={botLeft=" << m_bounds.m_bL
		<< ", dim=" << m_bounds.m_dim << "} is INTERNAL:\n";

      std::cout << "Bottom-Left-child:\n";
      if(botLeftTree == NULL) {
	std::cout << "[NULL]\n";
      }
      else {
	botLeftTree->dump();
      }
      std::cout << "Bottom-Right-child:\n";
      if(botRightTree == NULL) {
	std::cout << "[NULL]\n";
      }
      else {
	botRightTree->dump();
      }
      std::cout << "Top-Left-child:\n";
      if(topLeftTree == NULL) {
	std::cout << "[NULL]\n";
      }
      else {
	topLeftTree->dump();
      }
      std::cout << "Top-Right-child:\n";
      if(topRightTree == NULL) {
	std::cout << "[NULL]\n";
      }
      else {
	topRightTree->dump();
      }
    }
  }
}
QTNode::iterator QTNode::begin() {

}
QTNode::iterator QTNode::end() {

}
//  BBox m_bounds;  // The bounding box for this node
//  Point m_point;  // If leaf node (i.e., no kids), m_point, m_data hold the
//  int m_data;     // actual point and data value the user inserted.
//  QTNode *topLeftTree, *topRightTree, *botLeftTree, *botRightTree; // Child nodes
