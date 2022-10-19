class Clock             /* File: postoffice3.h */
{
  public:
    Clock()  { cout << "Clock Constructor\n"; }
    ~Clock() { cout << "Clock Destructor\n"; }
};

class Postoffice 
{
    Clock* clock;
  public:
    Postoffice() 
        { clock = new Clock; cout << "Postoffice Constructor\n"; }
    ~Postoffice()
        { cout << "Postoffice Destructor\n";  delete clock; }
};
