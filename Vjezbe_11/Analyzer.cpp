// Include classes
#include <Analyzer.h>

// Declaring default constructor
Analyzer::Analyzer()
{
  srand((unsigned)time(0));
}

// Destructor declaration
Analyzer::~Analyzer()
{
}


int Analyzer::Dice()
{
  int i;

  i = (rand()%6)+1;

  return i;
}

void Analyzer::ClopperPearsonInterval(int r, int N, double CL)
{
  cout << "Clopper-Pearson interval at " << CL*100 << "\% confidence level for " <<
          r << " successes out of " << N << " trials is [" << Analyzer::ClopperPearson_d(r,N,CL) <<
          "," << Analyzer::ClopperPearson_u(r,N,CL) << "]." << endl;
}

void Analyzer::DrawCPInterval(int N, double CL, int r)
{
  c = new TCanvas("c","c",900,700);
  CPInterval = new THStack("CPInterval","CPInterval");

  stringstream stream;
  stream << fixed << setprecision(2) << CL*100;
  TString CL_string = stream.str();

  histo_lowerValue = new TH1F("lower_value", "lower_value", N+1, 0, N+1);
  histo_upperValue = new TH1F("upper_value", "upper_value", N+1, 0, N+1);

  CPInterval->SetTitle("Clopper-Pearson " + CL_string + "\% confidence belt");

  histo_upperValue->SetFillColor(kBlue-1);
  histo_upperValue->SetLineColor(kBlue-1);
  histo_lowerValue->SetLineColor(kBlue-1);

  for(int i = 0; i <= N ; i++)
  {
    histo_lowerValue->SetBinContent(i+1,Analyzer::ClopperPearson_d(i,N,CL));
    histo_upperValue->SetBinContent(i+1,Analyzer::ClopperPearson_u(i,N,CL));

    histo_lowerValue->GetXaxis()->SetBinLabel(i+1,to_string(i).c_str());
    histo_upperValue->GetXaxis()->SetBinLabel(i+1,to_string(i).c_str());
  }

  CPInterval->Add(histo_lowerValue);
  histo_upperValue->Add(histo_lowerValue,-1);
  CPInterval->Add(histo_upperValue);

  CPInterval->Draw("HIST");

  CPInterval->GetXaxis()->SetTitle("N");
  CPInterval->GetYaxis()->SetTitle("p");

  l_x = new TLine(r+0.5,0.,r+0.5,histo_lowerValue->GetBinContent(r+1)+histo_upperValue->GetBinContent(r+1));
  l_x->SetLineStyle(kDashed);
  l_x->SetLineColor(kBlack);
  l_x->Draw();

  l_p1 = new TLine(0.,histo_lowerValue->GetBinContent(r+1),r+0.5,histo_lowerValue->GetBinContent(r+1));
  l_p1->SetLineStyle(kDashed);
  l_p1->SetLineColor(kRed);
  l_p1->Draw();

  l_p2 = new TLine(0.,histo_lowerValue->GetBinContent(r+1)+histo_upperValue->GetBinContent(r+1),r+0.5,histo_lowerValue->GetBinContent(r+1)+histo_upperValue->GetBinContent(r+1));
  l_p2->SetLineStyle(kDashed);
  l_p2->SetLineColor(kRed);
  l_p2->Draw();

  c->SaveAs("ClopperPearsonInterval.pdf");

  delete c,histo_lowerValue,histo_upperValue,CPInterval;

}

double Analyzer::ClopperPearson_d(int r, int N, double CL)
{
  double step = 0.001;
  double binomial_sum = 0.;
  double p_lower = 0.;
  double p_temp = 0.;

  for (int i_step = 0; i_step <= 1000; i_step++)
  {
    p_temp = 1.0 - i_step * step;

    for (int i = 0; i < r; i++)
    {
      binomial_sum += Analyzer::Binomial(i,p_temp,N);
    }

    if ( binomial_sum >= (1-(1-CL)/2) )
    {
      p_lower = p_temp;
      break;
    }
    else
    {
      binomial_sum = 0;
    }

  }

  return p_lower;
}

double Analyzer::ClopperPearson_u(int r, int N, double CL)
{
  double step = 0.001;
  double binomial_sum = 0.;
  double p_upper = 0.;
  double p_temp = 0.;

  for (int i_step = 0; i_step <= 1000; i_step++)
  {
    p_temp = i_step * step;

    for (int i = r+1; i <= N; i++)
    {
      binomial_sum += Analyzer::Binomial(i,p_temp,N);
    }

    if ( binomial_sum >= (1-(1-CL)/2) )
    {
      p_upper = p_temp;
      break;
    }
    else if (i_step == 1000)
    {
      p_upper = 1.00;
    }
    else
    {
      binomial_sum = 0;
    }

  }

  return p_upper;
}

// Function to calculate Binomial probability
double Analyzer::Binomial(int r, double p, int N)
{
  double bin = 0.;

  bin = static_cast<double>(Analyzer::Factorial(N)/(Analyzer::Factorial(r)*Analyzer::Factorial(N-r)))*pow(p,r)*pow(1-p,N-r);

  return bin;
}

long int Analyzer::Factorial( int n )
{
  long int factorial = 1;

  if ( n > 1 )
  {
    for(int i = 1; i <= n; i++)
    {
      factorial *= i;
    }
  }

  return factorial;
}
