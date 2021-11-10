// Include classes
#include <ElementaryParticle.h>

// Declaring default constructor
ElementaryParticle::ElementaryParticle()
{
  _name = "";
  _mass = 0.;
  _isBoson = false;

  _px = 0.;
  _py = 0.;
  _pz = 0.;
  _E = 0.;
}

// Declare overriding constructor
ElementaryParticle::ElementaryParticle(string name, float mass, bool isBoson)
{
  _name = name;
  _mass = mass;
  _isBoson = isBoson;

  _px = 0.;
  _py = 0.;
  _pz = 0.;
  _E = _mass;
}

// Destructor declaration
ElementaryParticle::~ElementaryParticle()
{
}

// Function for printing some basic information about the particle
void ElementaryParticle::printInfo()
{
  cout << "Particle named " << _name << " has a mass of " << _mass << " GeV." << endl;
  cout << "This particle is ";
  if ( !_isBoson ) cout << "not ";
  cout << "a boson!" << endl;
}


// Print four momentum of the particle
void ElementaryParticle::printP4()
{
  cout << "(" << _px << ", " << _py << ", " << _pz << ", " << _E << ")" << endl;
}

// Set the components of the momentum and calculate energy
void ElementaryParticle::setP( float p_x, float p_y, float p_z)
{
  _px = p_x;
  _py = p_y;
  _pz = p_z;
  _E  = sqrt(_px*_px + _py*_py + _pz*_pz + _mass*_mass);
}

// Set basic info about particle
void ElementaryParticle::setInfo( string name, float mass, bool isBoson )
{
  _name = name;
  _mass = mass;
  _isBoson = isBoson;
}

// Calculate pt of a particle
float ElementaryParticle::pt()
{
  return sqrt(_px*_px + _py*_py);
}


// Function to decay bosons to two particles
void ElementaryParticle::bosonDecay( ElementaryParticle *particle_1, ElementaryParticle *particle_2)
{
  if (!_isBoson)// Supports only boson decays
  {
    cout << "This function only supports boson decays and " << _name << " is not a boson!" << endl;
    return;
  }

  random_number = (rand()%1000) + 1;//Generate random number for decay

  if( random_number < 214) //21.4% decay to W+W-
  {
    particle_1->setInfo("W+", 80.4, true);
    particle_2->setInfo("W-", 80.4, true);
  }

  else if( random_number < 214 + 64) //(21.4% +) 6.4% decay to tau+tau-
  {
    particle_1->setInfo("tau+", 1.77, false);
    particle_2->setInfo("tau-", 1.77, false);
  }

  else if( random_number < 214 + 64 + 26)//(21.4% + 6.4% +) 2.6% decay to ZZ
  {
    particle_1->setInfo("Z", 91.2, true);
    particle_2->setInfo("Z", 91.2, true);
  }

  else // decay to bb
  {
    particle_1->setInfo("b", 4.18, false);
    particle_2->setInfo("b", 4.18, false);
  }

  //Decay kinematics
  // Make sure to take care of the conservation of momentum
  random_number_x = rand() % 100 + 1;

  if(random_number_x == 100) // handle special case so the code does not crash
  {
    random_number_y = 0;
    random_number_z = 0;
  }
  else
  {
    random_number_y = rand() % (100 - random_number_x) + 1;
    random_number_z = 100 - random_number_x - random_number_y;
  }

  // Set kinematics of decay particles
  particle_1->setP(_px*(random_number_x/100.),_py*(random_number_y/100.),_pz*(random_number_z/100.));
  particle_2->setP(_px - particle_1->_px, _py-particle_1->_py, _pz-particle_1->_pz);

}
