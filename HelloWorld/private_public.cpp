#include <iostream>
using namespace std;
#define PI 3.142
class numbers {
        // class data members are private by default:
        // can use {} and = but not () 
        int a {1000};
        int b = 200;
        int c = 0;
        public:
            void print_a_b(){
                c = 10000;
                cout<< "Print a and b "<< a<<" "<<b<< " "<<c<<endl;
            }
    };

int main(){

    numbers dennis;
    dennis.print_a_b();

    // try to modify a and b within class 
    //dennis.a = 100;
    //dennis.b = 1000;
    cout<<PI<<endl;

    dennis.print_a_b();
    return 0;
    
}