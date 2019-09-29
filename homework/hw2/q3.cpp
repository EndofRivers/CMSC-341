#include <iostream>
using namespace std ;

class Node {
public:
  int  m_data;
  Node *m_next;
};

//
// INSERT YOUR getListFromUser IMPLEMENTATION HERE
Node* getListFromUser();

Node* getListFromUser() {
  Node *head = NULL;
  int input;
  do {
    cout << "Enter numbers, 0 to stop\n";
    cin >> input;
    if(input != 0) {
      if(head == NULL) {
	Node *newNode = new Node();
	head = newNode;
	newNode->m_data = input;
      }
      else {
	Node *curr;
	curr = head;
	while(curr->m_next != NULL) {
	  curr = curr->m_next;
	}
	Node *tail = new Node();
	tail->m_data = input;
	curr->m_next = tail;
	tail->m_next = NULL;
      }
    }
  } while(input != 0);
  return head;
}
//

int main() {

  Node *head, *curr, *next;

  head = getListFromUser();
  next = head;
  while (next != NULL) {
    curr = next;
    next = curr->m_next;
    cout << "Next #: " << curr->m_data << endl;
    delete curr;
  }
  return 0;
}
