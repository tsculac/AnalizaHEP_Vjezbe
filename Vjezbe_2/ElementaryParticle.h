#include <iostream>

using namespace std;

// Declare class ElementaryParticle
class ElementaryParticle
{
  public:
    ElementaryParticle( string name, float mass, bool isBoson );
    ~ElementaryParticle( );

    string _name;
    float _mass;
    bool _isBoson;

    void printInfo();
};
