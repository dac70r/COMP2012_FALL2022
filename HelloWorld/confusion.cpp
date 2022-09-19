#include <iostream>

using namespace std;


int x = 5;
int *p = &x;
int **q = &p;
int ***r = &q;
int &xref = x;
int *xptr = &xref;
int z {'a'};

int main(){

    cout<< z <<endl;
    cout<< x <<endl;
    cout<< xref <<endl;
    cout<< *xptr <<endl;

    *xptr = 6;

    cout<< x <<endl;
    cout<< xref <<endl;
    cout<< *xptr <<endl;

    ***r = 100;
    cout<< x <<endl;
    cout<< xref <<endl;
    cout<< *xptr <<endl;

    int hehe {22 };

    cout<< hehe <<endl;

    int range [] {2,4,6,8,10};

    for (int k:range){
        cout<<k*k<<", "<<endl;
        cout<<k<<endl;
    }

    cout<<endl;

    for (int &k:range){
        k = k+2;
    }

    for (int &k:range){
        cout<<k<<endl;
    }
        






    return 0;
}

