// File: test2.cpp
//
// CMSC 341 Spring 2017 Project 4
//
// Check insert, deleteMin and deleteMax 
// with MinMaxHeap instantiated with string.
//
// Should compile with:  g++ test2.cpp
//

#include <iostream>
#include <string>
#include "MinMaxHeap.h"

using namespace std;

int main() {

  cout << "Saving strings into the heap\n";

  MinMaxHeap<string> S(25) ;
  S.insert("jkl") ;
  S.insert("yz_") ;
  S.insert("abc") ;
  S.insert("mno") ;
  S.insert("vwx") ;
  S.insert("pqr") ;
  S.insert("ghi") ;
  S.insert("def") ;
  S.insert("stu") ;

  S.dump() ;

  string answer ;
  answer = S.deleteMin() ;
  cout << "Min item " << answer << " removed from MinMax Heap\n" ;

  answer = S.deleteMax() ;
  cout << "Max item " << answer << " removed from MinMax Heap\n" ;

  S.dump() ;

  cout << "Saving ints into the Heap\n";
  cout << "Also testing Copy Constructor and AssOp\n";

  MinMaxHeap<int> H(25) ;
  H.insert(5) ;
  H.insert(10) ;
  H.insert(7) ;
  H.insert(9) ;
  H.insert(6) ;
  H.insert(2) ;
  H.insert(16) ;
  H.insert(12) ;
  H.insert(11) ;

  cout << "Initial MinMax Heap\n" ;
  H.dump() ;

  MinMaxHeap<int> *Gptr = new MinMaxHeap<int>(H) ;
  cout << "copied MinMax Heap\n" ;
  Gptr->dump();

  H.deleteMax() ;
  Gptr->deleteMin() ;

  delete Gptr ;

  H.deleteMin() ;
  H.deleteMax() ;

  MinMaxHeap<int> K1(11) ;
  K1.insert(29) ;
  K1.insert(24) ;
  K1.insert(23) ;
  K1.insert(22) ;
  K1.insert(28) ;
  K1.insert(26) ;
  K1.insert(30) ;
  K1.insert(21) ;
  K1.insert(25) ;
  K1.insert(27) ;


  MinMaxHeap<int> K2(4) ;
  K2.insert(43) ;
  K2.insert(42) ;
  K2.insert(44) ;
  K2.insert(41) ;


  K2 = K1 ;
  K1.deleteMax() ;
  K2.insert(57) ;

  cout << "Emptying everything in array\n";
  for(int i = 0; i < 9; i++)
    K1.deleteMax();
  K1.dump();
}
