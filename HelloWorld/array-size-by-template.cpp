#include <iostream>

using namespace std;

template <typename T, int haha>
    void hehe (T a){
        cout<<"haha is :"<<haha<<" a is :"<<a<<endl;
    }

int main(){

    
    hehe<int,20>(100);

    return 0;

}