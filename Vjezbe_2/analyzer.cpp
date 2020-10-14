// C++
#include <iostream>

// My own class
#include <ElementaryParticle.h>

using namespace std;

int main()
{
  ElementaryParticle Higgs("Higgs boson", 125.6, true);
  ElementaryParticle TopQuark("Top quark", 173.0, false);

  Higgs.printInfo();
  TopQuark.printInfo();

  ElementaryParticle *Z;
  Z = new ElementaryParticle("Z boson", 91.2, true);
  Z->printInfo();
  Z->~ElementaryParticle();

  return 0;
}
