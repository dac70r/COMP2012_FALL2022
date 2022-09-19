#include<iostream>
using namespace std;

//class

class Person {

    private:
        string name;
        char gender;
        int age;

    public:
        Person(string poipoiyoshi, char b, int c)
        {
            name = poipoiyoshi;
            gender = b;
            age = c;
            cout<<"Object Created"<<endl;
        }

        void sayHaha() const { // const after the paranthesis of member function -> not allowed to change data member values 
            cout<<"name"<<endl;
            // age = 99;       // <- syntax correct but bad taste
        } 

        int getAge() const{ // accessor, shouldn't be allowed to change any values so must add const
            // cout << "Desmond is a good guy!"<<endl; <- do not add this line (only accessing stuff)
            return age;
        }

        void changeAge(int new_age) { // no const here because we must allow it to be be modified. 
            age = new_age; // question: why don't we make the age data member to be public? 
            // protection. we can set if statements here to restrict the changed value. 
        }


};

struct Persons {
    int age;
    string name;

};

class Personnel {
    private:
        const char* _name; // <- added const 
    public: 
        Personnel(const char* n){ // meaning: we cannot change the thing pointed by n 
            _name = n; // we can use _name to change n if _name isn't const, 
            // so at the top we added const

        }
        const char* getName() const{ // accessor, shouldn't be allowed to change any values so must add const
            return _name;
        }
};

class Name {

    public:
        const char *name;
};

class Word {
    private: int frequency;

    public: Word(){frequency = 100;}
        void printWord(){
            cout<<frequency<<endl;
        }
};

class Integer{
    private: 
        int value;
    public:
        Integer (int v){value = v;}

        Integer add1(const Integer &i){
            value += i.value;
            return *this;  // Start from (this) across the arrow to i1 (return i1)
        } // creates a copy of this object

        Integer& add2(const Integer &i){
            value += i.value;
            return *this;
        } // 

        Integer* add3(const Integer &i){
            value += i.value;
            return this;
        }

        void print_value() const{
            cout<<"Total value is: "<<this->value<<endl;
        } 
};


int main(){

    Person desmond("Dennis",'M',22); // we call 'desmond' an object 
    Personnel dennis("Dennis"); 
    desmond.sayHaha();
    cout<<desmond.getAge()<<endl;
    cout<<dennis.getName();
    //desmond.name = 'Desmond'; <- inaccessible 

    Persons James;
    Persons Johannas;
    //Johannas = James;
    James.name = "James";
    James.age = 15;
    Johannas = James;
    cout<<"James is :"<<James.age<<" years old"<<endl;

    Name Dennis = {"Dennis"}; // 
    Name Jameson {"Jameson"}; // 
    // local variabes are not initialized 

    Word hello;
    hello.printWord();
    Integer numba_one(100);
    Integer numba_two(200);
    Integer numba_three = numba_one.add1(numba_two);
    numba_one.print_value(); // why isn't numba 1: 100? because numba_one already added by numba_two
    numba_three.print_value(); // creates a copy of numba1 put in in numba3

    //Integer numba_four = numba_one.add2(numba_two); // a copy of i1 put in i3 
    //numba_four.print_value();

    Integer & numba_five = numba_one.add2(numba_two);
    numba_five.print_value();
    numba_one.print_value();
    numba_one.add1(numba_two);
    numba_five.print_value(); // why numba_one add 200, numba_five also add 200? 
    // because numba_five is a reference of numba_one

    // if you define a nickname without const, then this nickname for those
    // with a name, so poor guy cannot 
    // Integer &numba_six = numba_one.add2(numba_two).add1(numba_two);

    // in order to define a nickname for a poorguy you need a const
    const Integer &numba_six = numba_one.add2(numba_two).add1(numba_two);

    // 


}

