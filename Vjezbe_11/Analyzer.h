#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

//ROOT headers
#include <TROOT.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TString.h>
#include <TH1.h>
#include <THStack.h>
#include <TLine.h>

using namespace std;

// Declare class Analyzer
class Analyzer
{
  // public member declaration
  public:
    Analyzer( );
    ~Analyzer( );

    int Dice();
    void ClopperPearsonInterval( int r, int N, double CL);
    void DrawCPInterval( int N, double CL, int r);
    double ClopperPearson_d( int r, int N, double CL);
    double ClopperPearson_u( int r, int N, double CL);
    double Binomial( int r, double p , int N);

  // private member declaration
  private:
    long int Factorial( int n );

    THStack *CPInterval;
    TH1 *histo_lowerValue;
    TH1 *histo_upperValue;
    TCanvas *c;
    TLine *l_x,*l_p1,*l_p2;
};
