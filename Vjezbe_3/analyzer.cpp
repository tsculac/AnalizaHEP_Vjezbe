// C++
#include <iostream>
#include <fstream>

// My own class
#include <ElementaryParticle.h>

using namespace std;

int main()
{
  // Declare variables needed for random number generation
  int x_rand, y_rand, z_rand;
  srand(time(NULL));

  // Output file creation
  ofstream myfile;
  myfile.open ("Analysis.txt");

  // Declare Higgs object that will decay
  ElementaryParticle *Higgs;

  Higgs = new ElementaryParticle("Higgs", 125.6, true);

  // Declare two decay products of Higgs
  ElementaryParticle *decayParticle_1, *decayParticle_2;
  decayParticle_1 = new ElementaryParticle();
  decayParticle_2 = new ElementaryParticle();

  // Include output format information in the header of the file
  myfile << "EventNumber DecayParticle1_Name DecayParticle1_isBoson DecayParticle1_mass DecayParticle1_px DecayParticle1_py DecayParticle1_pz DecayParticle1_E DecayParticle1_pt" <<
                       " DecayParticle2_Name DecayParticle2_isBoson DecayParticle2_mass DecayParticle2_px DecayParticle2_py DecayParticle2_pz DecayParticle2_E DecayParticle2_pt" << endl;

  for(int i_event = 0; i_event < 10000; i_event++) // Generate 10000 events
  {
    // Generate random numbers in the [-1000,1000] interval
    x_rand = -1000 + rand() % 2000;
    y_rand = -1000 + rand() % 2000;
    z_rand = -1000 + rand() % 2000;

    // Set the momentum of Higgs to random values in range [-100.0,100.0]
    Higgs->setP(x_rand/10., y_rand/10., z_rand/10.);

    // Decay Higgs boson
    Higgs->bosonDecay(decayParticle_1, decayParticle_2);

    // Save information about decay products in the txt file
    myfile << i_event << " " << decayParticle_1->_name << " "<< decayParticle_1->_isBoson << " " << decayParticle_1->_mass << " "
                             << decayParticle_1->_px << " " << decayParticle_1->_py << " " << decayParticle_1->_pz << " " << decayParticle_1->_E << " " << decayParticle_1->pt() << " "
                             << decayParticle_2->_name << " "<< decayParticle_2->_isBoson << " " << decayParticle_2->_mass << " "
                             << decayParticle_2->_px << " " << decayParticle_2->_py << " " << decayParticle_2->_pz << " " << decayParticle_2->_E << " " << decayParticle_2->pt() << endl;

  }
  // Close the file
  myfile.close();

  // Call destructor for all pointers
  Higgs->~ElementaryParticle();
  decayParticle_1->~ElementaryParticle();
  decayParticle_2->~ElementaryParticle();

  return 0;
}
