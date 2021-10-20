// Include classes
#include <ElementaryParticle.h>

// Declaring constructor
ElementaryParticle::ElementaryParticle(string name, float mass, bool isBoson)
{
  _name = name;
  _mass = mass;
  _isBoson = isBoson;

}

ElementaryParticle::~ElementaryParticle()
{
}

void ElementaryParticle::printInfo()
{
  cout << "Particle named " << _name << " has a mass of " << _mass << " GeV." << endl;
  cout << "This particle is ";
  if ( !_isBoson ) cout << "not ";
  cout << "a boson!" << endl;
}
