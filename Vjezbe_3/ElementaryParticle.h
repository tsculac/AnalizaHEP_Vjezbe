#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Declare class ElementaryParticle
class ElementaryParticle
{
  // public member declaration
  public:
    ElementaryParticle( ); // constructor
    ElementaryParticle( string name, float mass, bool isBoson ); // override of the constructor
    ~ElementaryParticle( ); // destructor

    string _name;
    float _mass;
    bool _isBoson;

    float _px,_py,_pz,_E;

    void printInfo();
    void printP4();

    void setP( float p_x, float p_y, float p_z );
    void setInfo( string name, float mass, bool isBoson );

    float pt();

    void bosonDecay( ElementaryParticle* particle_1, ElementaryParticle* particle_2);

  // private member declaration
  private:
    int random_number;
    int random_number_x, random_number_y, random_number_z;
};
