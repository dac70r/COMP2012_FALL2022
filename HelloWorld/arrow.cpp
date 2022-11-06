#include <iostream>
using namespace std;


int main(){

    /*
    int a = 100;
    class A{
        private: 
            int b = 10;
        public:
            int print_info (){
                return b;
            }
    };
    int* p = &a;

    A america;
    A* americas = &america;
    cout<<americas->print_info();
    */
   const int val1 = 100;
   int val2 = val1;

   const int& val3 = val1;
    int val4 = val3;

    const int& val5 = val3;
    const int& val6 = val1;
   //val2 = 1000;
   cout<<val2<<endl;

   const int& hall = val1;
   cout<<&hall<<endl;

   class A {
    int a;
        public:
            void print_info (){
                cout<<a<<endl;
            }
            A(int a) {
            this->a = a;}
            void change_a(){
                a = 123;
            }
        ~A(){
            
            cout<<"destructor called"<<endl;
            cout<< this->a<<endl;
        }
    };


    const int integer1 = 10;
    

    A obj = A(1);
    cout<<"-------"<<endl;
    cout<<"Printing obj info : "<<endl;
    obj.change_a();
    obj.print_info();
    
    



}