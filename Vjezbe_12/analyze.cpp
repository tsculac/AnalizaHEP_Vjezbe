// C++
#include <iostream>
#include <fstream>

// My own class
#include <Analyzer.h>

using namespace std;

int main()
{
  // Declare Analyzer
  Analyzer *analyzer;

  analyzer = new Analyzer();

  analyzer->Loop();

  analyzer->MVATraining("GBDT");
  // analyzer->MVATraining("kMLP");

  analyzer->PlotMVAScore("GBDT");
  // analyzer->PlotMVAScore("kMLP");

  delete analyzer;

  return 0;
}
