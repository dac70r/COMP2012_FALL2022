#include <iostream>

using namespace std;

int main(){


    
    int arr[] = {0,2,3,1};
    int size = sizeof(arr)/sizeof(int);
    cout<<"Size of arr is :"<<size<<endl;
    for (int k=0;k<size;k++){
        for (int j=0;j<size-1;j++){
            //cout<<"arr : "<<arr[j]<<endl;
            if (!(arr[j]<arr[j+1])){

                cout<<arr[j]<<" is "<<"Smaller than "<<arr[j+1]<<endl;
            }

        }
    } 

    return 0;
}