#include <iostream>
using namespace std ;

int binarySearch(int *myNums, int cnt, int val);

int binarySearch(int *myNums, int cnt, int val) {
  int high = cnt - 1;
  int low = 0;

  while(low <= high) {
    int mid = low + ((high - low) / 2);
    
    if(myNums[mid] == val)
      return mid;

    if(myNums[mid] > val)
      high = mid - 1;

    else
      low = mid + 1;
  }
  return -1;
}

//
// INSERT YOUR binarySearch IMPLEMENTATION HERE
//

int main() {

  int val, myNums[1000];  // Yuck--magic number!
  int pos, cnt = -1;

  cout << "Enter numbers from smallest to largest, 0 to stop\n";
  do {
    cin >> myNums[++cnt];
  } while (myNums[cnt] != 0);

  do {
    cout << "Enter number to search for: ";
    cin >> val;
    if (val != 0) {
      pos = binarySearch(myNums, cnt, val);
      cout << "binarySearch reported " << pos << endl;
    }
  } while (val != 0);

  return 0 ;
}
