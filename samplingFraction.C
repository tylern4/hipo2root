#include "TH2.h"
#include "TLorentzVector.h"

std::vector<int> *pid;
std::vector<float> *px;
std::vector<float> *py;
std::vector<float> *pz;

std::vector<float> *ec_tot_energy;

TH2D *sf_hist = new TH2D("sf_hist", "Electron Sampling Fraction", 500, 0, 3.5, 500, 0, 0.5);
TChain *clas12 = new TChain("clas12", "clas12");

int samplingFraction() {
  clas12->Add("test.root");

  clas12->SetBranchAddress("pid", &pid);
  clas12->SetBranchAddress("px", &px);
  clas12->SetBranchAddress("py", &py);
  clas12->SetBranchAddress("pz", &pz);

  clas12->SetBranchAddress("ec_tot_energy", &ec_tot_energy);

  int num_of_events = (int)clas12->GetEntries();
  TLorentzVector elec;
  for (int current_event = 0; current_event < num_of_events; current_event++) {
    clas12->GetEntry(current_event);
    elec.SetXYZM(px->at(0), py->at(0), pz->at(0), 0.000511);
    if (elec.P() != 0) sf_hist->Fill(elec.P(), ec_tot_energy->at(0) / elec.P());
  }

  sf_hist->Draw("colz");

  return 1;
}
