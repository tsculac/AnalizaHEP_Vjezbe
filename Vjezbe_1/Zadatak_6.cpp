#include <iostream>

using namespace std;

// Declare class ElementaryParticle
class ElementaryParticle
{
    // Declare public members that can be called by objects of type ElementaryParticle
    public:

    string _name;
    float _mass;
    bool _isBoson;


    // Default Constructor
    ElementaryParticle( )
    {
        _name = "";
        _mass = 0;
        _isBoson = false;
    }

    // Override of the Constructor
    ElementaryParticle( string name, float mass, bool isBoson)
    {
        _name = name;
        _mass = mass;
        _isBoson = isBoson;
    }

    void printInfo()
    {
       cout << "Particle named " << _name << " has a mass of " << _mass << " GeV." << endl;
       cout << "This particle is ";
       if ( !_isBoson ) cout << "not ";
       cout << "a boson!" << endl;
    }
};

int main() {

    // // Solution A.-D.
    // // Declare an object of class ElementaryParticle
    // ElementaryParticle Higgs;
    // ElementaryParticle TopQuark;
    //
    // // Declare object properties accessing public class members
    // Higgs._name = "Higgs boson";
    // Higgs._mass = 125.26;
    // Higgs._isBoson = true;
    //
    // TopQuark._name = "Top quark";
    // TopQuark._mass = 173.0;
    // TopQuark._isBoson = false;
    //
    // // accessing member functions
    // Higgs.printInfo();
    // TopQuark.printInfo();
    //
    // // Declare a pointer to an object of class ElementaryParticle
    // ElementaryParticle *Z;
    //
    // Z->_name = "Z boson"; // Is this correct? What are you declaring here?
    // Z->_mass = 91.12;
    // Z->_isBoson = true;
    //
    // Z->printInfo(); //Do you understand why this line gives a segfault?

    ElementaryParticle Higgs("Higgs boson", 125.6, true);
    ElementaryParticle TopQuark("Top quark", 173.0, false);

    Higgs.printInfo();
    TopQuark.printInfo();

    ElementaryParticle *Z;
    Z = new ElementaryParticle("Z boson", 91.2, true);
    Z->printInfo();
    delete Z;

    return 0;
}
