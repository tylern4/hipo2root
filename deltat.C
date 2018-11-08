#include "TH2.h"
#include "TLorentzVector.h"

static const int MAX = 50;
int gpart;
int pid[MAX];
float p[MAX];

float sc_ftof_time[MAX];
float sc_ftof_path[MAX];

static const double MASS_P = 0.93827203;
const double c_special_units = 29.9792458;

double vertex_time(double sc_time, double sc_pathlength, double relatavistic_beta) {
  return sc_time - sc_pathlength / (relatavistic_beta * c_special_units);
}

TH2D *deltaT_prot = new TH2D("deltaT_prot", "#DeltaT Proton", 500, 0, 5.0, 500, -5, 5);
TChain *clas12 = new TChain("clas12", "clas12");

int deltat() {
  clas12->Add("test.root");

  clas12->SetBranchAddress("gpart", &gpart);
  clas12->SetBranchAddress("pid", &pid);
  clas12->SetBranchAddress("p", &p);

  clas12->SetBranchAddress("sc_ftof_time", &sc_ftof_time);
  clas12->SetBranchAddress("sc_ftof_path", &sc_ftof_path);

  int num_of_events = (int)clas12->GetEntries();
  for (int current_event = 0; current_event < num_of_events; current_event++) {
    clas12->GetEntry(current_event);
    double vertex = vertex_time(sc_ftof_time[0], sc_ftof_path[0], 1.0);

    for (size_t part = 1; part < gpart; part++) {
      if (p[part] == 0) continue;
      double beta = 1.0 / sqrt(1.0 + (MASS_P / p[part]) * (MASS_P / p[part]));
      double dt_P = vertex - vertex_time(sc_ftof_time[part], sc_ftof_path[part], beta);
      deltaT_prot->Fill(p[part], dt_P);
    }
  }

  TCanvas *c1 = new TCanvas("c1", "c1");
  c1->cd();
  deltaT_prot->Draw("colz");

  return 1;
}
