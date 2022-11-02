#include <iostream>
#include <cstring>
using namespace std;

class TrivialClass {
public: 
  TrivialClass(const std::string& data) :
    mData(data) {};

  const std::string& getData(const TrivialClass& rhs) const {
    return rhs.mData;
  };

private:
  std::string mData;
};

int main() {
  TrivialClass a("fish");
  TrivialClass b("heads");

  std::cout << "b via a = " << a.getData(b) << std::endl;
  return 0;
}