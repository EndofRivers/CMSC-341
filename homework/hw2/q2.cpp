#include <iostream>
using namespace std;

int binarySearch(int *myNums, int cnt, int val);
int binarySearch(int *myNums, int cnt, int val) {

    int mid = cnt / 2;
    int target;

    if(myNums[mid] == val)
      return mid;

    else if(cnt == 1)
      return -1;

    else if(myNums[mid] > val)
      return binarySearch(myNums, mid, val);
    
    else {
      target = binarySearch(&myNums[mid], (cnt + 1)/2, val);
      if(target == -1)
	return -1;
      else
	return (mid + target);
    }
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
