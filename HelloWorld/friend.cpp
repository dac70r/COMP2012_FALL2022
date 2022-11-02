// classes_as_friends1.cpp
// compile with: /c
#include <iostream>
using namespace std;

class B;

class A {
public:
   void Func1( B& b );

private:
   int Func2( B& b );
};

class B {
private:
   int _b = 100;

   // A::Func1 is a friend function to class B
   // so A::Func1 has access to all members of B
   friend void  A::Func1( B& );

   public: 
   void print_info(){cout<<_b;}
   //friend int A::Func2 (B& ); 
};

void A::Func1( B& b ) { b._b = 123; }   // OK
//int A::Func2( B& b ) { return b._b; }   // C2248

int main(){

    A apple; B bunny;
    bunny.print_info();
    cout<<endl;
    apple.Func1(bunny);
    bunny.print_info();

    return 0;   
}