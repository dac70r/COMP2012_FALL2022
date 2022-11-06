#include <iostream>
using namespace std;
int main() {


  int val2 = 5;
  const int& ref2 = val2;
  int& ref1 = val2;
  ref1 = 100;
  //ref2 = 1000; //cannot use ref2 to change val2

  cout<< "ref2 "<<ref2<<endl;
  float apple = 2.3;

  for (int i=1;i<10;i++){
        cout<<[=](int k)mutable->int {apple = ref2 * i * apple; return apple; }(i)<<endl;
        //cout<<[&](int k){ref2 = ref2 * x; cout<<"x: "<<x<<endl; return ref2;}(x)<<endl;
        //cout<<[&ref1,&ref2](int x){ref1 = ref2 * x; return ref1; }(i)<<endl; // i does not need to be captured 
  }
  return 0;
}