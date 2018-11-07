#include "TH2.h"
#include "TLorentzVector.h"

int pid[50];
float p[50];
float beta[50];
int gpart;

TH2D *pvsb = new TH2D("pvsb", "Momentum vs Beta", 500, 0, 3.5, 500, 0, 1.2);

TChain *clas12 = new TChain("clas12", "clas12");

int pvsb() {
  clas12->Add("test.root");
  clas12->SetBranchAddress("gpart", &gpart);
  clas12->SetBranchAddress("pid", &pid);
  clas12->SetBranchAddress("p", &p);

  clas12->SetBranchAddress("beta", &beta);

  int num_of_events = (int)clas12->GetEntries();
  for (int current_event = 0; current_event < num_of_events; current_event++) {
    clas12->GetEntry(current_event);
    for (size_t i = 1; i < gpart; i++) {
      if (beta[i] < 0.05) continue;
      pvsb->Fill(p[i], beta[i]);
    }
  }

  TCanvas *c1 = new TCanvas("c1", "c1");
  c1->cd();
  pvsb->Draw("colz");

  return 1;
}
