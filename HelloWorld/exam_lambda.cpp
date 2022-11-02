#include <iostream>
using namespace std;
int main() {


  int val2 = 5;
  const int& ref2 = val2;
  float apple = 2.3;

  for (int x=1;x<10;x++){
        //cout<<[=](int k)mutable->int {apple = ref2 * x * apple; return apple; }(x)<<endl;
        cout<<[&](int k){ref2 = ref2 * x; cout<<"x: "<<x<<endl; return ref2;}(x)<<endl;
  }
  return 0;
}