#include "QTree.h"
QTree::QTree() {
  m_root = NULL;
}
QTree::~QTree() {
  delete m_root;
}
bool QTree::add(const Point &pt, int data) {
  // EDGE CASE: Adding the first node
  if(m_root == NULL) {
    m_root = new QTNode();
    m_root->add(pt, data);
    return true;
  }
  if(!m_root->m_bounds.inBounds(pt)) {
    m_root->m_bounds.resize(m_root->m_point, pt);
  }

  m_root->add(pt, data);
  return true;
}
bool QTree::remove(const Point &pt) {
  bool empty = true;
  if(m_root == NULL)
    return false;
  else {
    if(m_root->remove(pt, empty))
      return true;
    else
      return false;
  }
}
bool QTree::find(const Point &pt, int &data) {
  if(m_root == NULL)
    return false;
  else {
    if(m_root->find(pt, data))
      return true;
    else 
      return false;
  }
}
int QTree::findPoints(const BBox &region, std::vector<Point> &found) {

  return -1;
}
void QTree::dump() {
  std::cout << "============================================================\n";
  std::cout << "START Dump of quadtree\n";
  std::cout << "------------------------------------------------------------\n";
  m_root->dump();
  std::cout << "------------------------------------------------------------\n";
  std::cout << "END Dump of quadtree\n";
  std::cout << "============================================================\n";
}
