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

  int N_trials = 10;
  double ConfidenceLevel = 0.6827;
  //double ConfidenceLevel = 0.9545;

  int covered = 0;
  int six = 0;
  double p_minus[10];
  double p_plus[10];

  for(int i = 0; i < N_trials ; i++)
  {
    analyzer->ClopperPearsonInterval(i,N_trials,ConfidenceLevel);
    p_minus[i]=analyzer->ClopperPearson_d(i,N_trials,ConfidenceLevel);
    p_plus[i] =analyzer->ClopperPearson_u(i,N_trials,ConfidenceLevel);
  }

  analyzer->DrawCPInterval(N_trials, ConfidenceLevel, 3);

  for(int i = 0; i < 1000; i++)
  {
    for (int j = 0; j < N_trials; j++)
    {
      if (analyzer->Dice() == 6) six++;
    }

    if( p_minus[six] <= 1./6. && p_plus[six] >= 1./6.) covered++;

    six = 0;
  }

  cout << "For " << ConfidenceLevel*100. << "\% CL, true value vas covered by The ClopperPearson interval " << covered/10. << "\% of times." << endl;

  delete analyzer;

  return 0;
}
