#include <iostream>
using namespace std;

// const variable, const func parameter, const object, const member func
// const with pointer variable, 

int main(){

    int x = 5;
    const int *p = &x; // this is same as int const *p = &x;

    int a = 100;
    //*p = 100; // cannot changing the value of x using p, but can change x
    // can you change the value of p? yes, only cannot change 
    // the value of x using p
    
    p = &a; //ok can change p!
    //*p = 100; // not ok cannot change x using p


    // second const example 
    int y = 6;
    int* const q = &y;

    //q = &y; // not ok cannot use q to change address if y
    *q = 100; // ok can use q to change y 
    y = 100; // can change y? yes!

    // third const example
    int z = 6;
    const int * const r = &z;
    // same as const int const * p = &x;
    // same as int const* const p = &x;

    //*z = 100; not ok
    //z = &a; not ok 

    // const int zee = int const zee; 
    // same thing !!!!!!!!!!!!!!!!!!!
}

