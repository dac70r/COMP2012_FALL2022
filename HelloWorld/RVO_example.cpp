#include <iostream>

using namespace std;

class Test {
    int data;

    public: 
        Test (int data): data(data){
            cout<<"Conversion ctor"<<endl;
        }

        Test (const Test&t ): data(t.data){
            cout<<"copy ctor"<<endl;
        }
};

int main()
{
    Test object_test = Test(2);
    //Test first_test(Test(2));
    return 0; 
}