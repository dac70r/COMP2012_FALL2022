#include <iostream>     /* File: template-problem.cpp */
#include "string.h"
using namespace std;

template <typename T> const T&
    larger(const T& a, const T& b) { return (a < b) ? b : a; }

int main()
{
    // microsoft -> addr: 1000
    // apple -> addr: 1004 
    const char* m = "microsoft";
    const char* a = "apple";
    const string mic = "microsoft";
    const string apple = "apple";
    // what happens here is we are comparing the address value instead of the actual strcmp 
    
    cout << larger(a, m) << " is better!" << endl;
    cout << larger(m, a) << " is better!" << endl;

    cout << larger(mic, apple )<< " is better!"<<endl;
    cout << larger<string>(apple,mic )<< " is better!"<<endl;

    return 0;
}


