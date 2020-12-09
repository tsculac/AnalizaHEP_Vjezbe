#define Analyzer_cxx
#include "Analyzer.h"


void Analyzer::MLFit()
{
   TCanvas *c = new TCanvas("c","c",1800,600);
   c->Divide(3);

   histo = new TH1F("histo","Lifetime measurement",10,0.,10.);

   float sum_t = 0;
   int n_entries = 0;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      histo->Fill(t);

      sum_t += t;
      n_entries++;
   }

   c->cd(1);
   gPad->SetLeftMargin(0.15);

   FitFunction = new TF1("FitFunction","([0]/[1])*TMath::Exp(-x/[1])",0.,10.);
   FitFunction->SetParameters(1.,100.);

   histo->Fit(FitFunction);
   gStyle->SetOptFit();

   histo->GetXaxis()->SetTitle("t [s]");
   histo->GetYaxis()->SetTitle("Events / 1 s");

   histo->SetTitle("Lifetime measurement");

   histo->Draw();

   c->cd(2);
   gPad->SetLeftMargin(0.20);

   Likelihood = new TF1("Likelihood function","TMath::Power(x,-[0])*TMath::Exp(-[1]/x)",0.,10.);
   Likelihood->SetParameters(1, 1.);

   Likelihood->SetTitle("Likelihood function;#Tau;L");
   Likelihood->Draw();

   c->cd(3);
   gPad->SetLeftMargin(0.15);

   LogLikelihood = new TF1("Log-Likelihood function","2*([0]*TMath::Log(x)+[1]/x)",1.15,1.35);
   LogLikelihood->SetParameters(n_entries, sum_t);

   cout << endl;
   cout << "==============================================================" << endl;
   cout << "Analyticaly calculated from the ML method: tau = " << sum_t/n_entries << endl;
   cout << "Analyticaly calculated standard deviation: sigma = " << sum_t/TMath::Sqrt(TMath::Power(n_entries,3)) << endl;
   cout << "==============================================================" << endl;
   cout << endl;

   LogLikelihood->SetTitle("Log-Likelihood function;#Tau;-2lnL");
   LogLikelihood->Draw();

   float tau_hat;
   float sigma_m, sigma_p;

   tau_hat = LogLikelihood->GetMinimumX();
   sigma_m = tau_hat - LogLikelihood->GetX(LogLikelihood->GetMinimum()+1.,1.0,tau_hat-0.01);
   sigma_p = LogLikelihood->GetX(LogLikelihood->GetMinimum()+1.,tau_hat, 10.0) - tau_hat;

   cout << endl;
   cout << "==============================================================" << endl;
   cout << "Parameter value determined from the minimum of the -2lnL funciton: tau = " << tau_hat << endl;
   cout << "Standard deviation determined as -2lnL+1: sigma_+ = " << sigma_p << " sigma_- = " << sigma_m << endl;
   cout << "==============================================================" << endl;
   cout << endl;


   c->SaveAs("MaximumLikelihoodFit.pdf");
}
