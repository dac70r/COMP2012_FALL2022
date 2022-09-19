#include<iostream>
#include<typeinfo>

using namespace std;

int main (){

    int a[5];
    int b =10;

    cout<<"Address of a[0]  "<< &a[0]<<endl;
    cout<<"Address of a     "<< a<<endl; 

    //assigning 5 to a[0]
    a[0] = 5;
    cout<<"Value of a[0] "<< a[0] <<endl; 
    cout<<"Value of a[0] "<< typeid(&a[0]).name() <<endl; // Pi stands for pointer to int variable
    cout<<"Value of a[0] "<< typeid(&a).name() <<endl; // pointer to an array of 5 integers 
    cout<<"Value of a[0] "<< typeid(a).name() <<endl; // array of 5 integers 
    //assigning 10 to a[0]
    *a = 10; 
    cout<<"Value of a[0] "<< a[0] <<endl; 

    //assigning 5 to a[1]
    a[1] = 5;
    cout<<"Value of a[1] "<< a[1] <<endl; 

    //assigning 10 to a[1]
    *(a+1) = 10; 
    cout<<"Value of a[1] "<< a[1] <<endl; 

    int *pa = &b;
    cout<<sizeof(pa)<<endl;

    return 0; 
}