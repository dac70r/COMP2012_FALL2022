#include <iostream>
#include "B.h"
using namespace std;

inline void func(){
    cout<<"New York"<<endl;
}

class object_a {
    int a =100;
};

class object_b{
    int b = 200;
    public: 
        
};

class object_c {
    int c =300;
    object_a A;
    object_b B;
    public: 
        void get_A(){cout<<A.a<<endl;}
};

class A: public B
{
    public: 
        A(){cout<<"Hello World";}
        void print_info(){cout<<"B is : "<<B::a<<endl;};
};

int main(){

    A helloworld;
    A& happy = helloworld;
    func();
    A nigga;
    nigga = happy;

    int p = *(new int);
    int* p1 = new int;
    *p1 = 100;
    cout<<*p1<<endl;
    
    helloworld.print_info();
    return 0;
}