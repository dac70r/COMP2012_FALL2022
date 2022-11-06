#include <iostream> 
using namespace std; 

class A { public: void nonConstMemFunc() { } 
void constMemFunc() const { } 
const 
const A getConstObj () { return *this; } 
const A& getConstRefObj() { return *this; } }; 

int main() { 
const A constObj; 
constObj.nonConstMemFunc(); 
constObj.constMemFunc();
A nonConstObj; 
const A nonConstObj2 = nonConstObj.getConstObj();
A nonConstObj3 = nonConstObj.getConstRefObj(); 
A& nonConstRefObj1 = nonConstObj.getConstObj(); 
A& nonConstRefObj2 = nonConstObj.getConstRefObj(); 
const A constObj2 = nonConstObj.getConstObj(); 
const A constObj3 = nonConstObj.getConstRefObj(); 
const A& constRefObj1 = nonConstObj.getConstObj(); /* Error: /* Error: /* Error: /* Error: /* Error: /* Error: /* Error: /* Error: /* Error: const A& constRefObj2 = nonConstObj.getConstRefObj(); /* Error: A& const mystery = nonConstObj.getConstObj(); return 0; }