#include <iostream>

using namespace std;



class A{
    private: int a=10;
    friend class B; // allow B to access A 
};

class B{
    private: int b;
    public: 
    void display(A& t){
        cout<<"Return "<<t.a<<endl;
    }
};

int main(){

    A apple;
    B boy; 
    boy.display(apple);

    return 0;
}