#include <iostream>

using namespace std;

float _my_cube( float x )
{
  return x*x*x;
}

int main()
{
  float x = 0.;

  cout << "What is the number you want me to calculate with? ";
  cin >> x;
  cout << "The cube of " << x << " is " << _my_cube(x) << endl;
  
  return 0;
}
