#include <iostream>

using namespace std;


class Cell{

    int age; 
};

class List {

    int size = 100;
    int human {20};
    //int hello (12); // <- cannot initialize data members using paranthesis, other 
    Cell* cellulose; // methods is okay 


};

int main(){

    cout<<sizeof(List)<<endl;
    int nigga (90); // <- global/ local scope but not class scope  
    return 0; 
}