#include<iostream>
#include "string.h"

class Word              /* File: public-member-init.cpp */
{
  int dennis = 0;
  public:
    int frequency = 200;//{2000};
    const char* str = "a";//{nullptr};
    //Word(){frequency = 100;str==nullptr;};
    //Word()
    //Word(){};
    Word (int h){frequency = h;};
    //Word (const char* c){std::cout<<c;};
};

class UPerson{
  int a = 0;
  public: 
    int frequency;

    UPerson(int f=123){
        frequency = f;
    }


};

int main() { //Word movie = {1, "Titanic"}; 

  //Word director; 
  //std::cout<<director.frequency<<"\n";
  //std::cout<<movie.frequency<<"\n";
  //std::cout<<movie.str;
  //Word director (2,"Nemo"); 
  //std::cout<<director.frequency;
  //std::cout<<director.str;
  // Word brian(11200);
  //std::cout<<brian.dennis;
  //std::cout<<brian.frequency;
  UPerson Mary; 
  std::cout<<Mary.frequency;


  // without MIL 
  //Word director {0,"James Cameron"};


  return 0;
}


