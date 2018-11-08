/*
 *
 * Author: Nick Tyler, University Of South Carolina
 */
// Standard libs
#include <time.h>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>
// ROOT libs
#include "TFile.h"
#include "TTree.h"
// Hipo libs
#include "reader.h"

#define NaN std::nanf("-9999")

static const int MAX = 100;

int nCrate;
int nTime;
int run;
int event;
float torus;
float solenoid;
int crate[MAX];
int slot[MAX];
int channel[MAX];
int helicity[MAX];
int quartet[MAX];
int value[MAX];
float STTime[MAX];
float RFTime[MAX];

int gpart;
int pid[MAX];
float p[MAX];
float p2[MAX];
float px[MAX];
float py[MAX];
float pz[MAX];
float vx[MAX];
float vy[MAX];
float vz[MAX];
int charge[MAX];
float beta[MAX];
float chi2pid[MAX];
int status[MAX];

int dc_sec[MAX];
float dc_px[MAX];
float dc_py[MAX];
float dc_pz[MAX];
float dc_vx[MAX];
float dc_vy[MAX];
float dc_vz[MAX];

float cvt_px[MAX];
float cvt_py[MAX];
float cvt_pz[MAX];
float cvt_vx[MAX];
float cvt_vy[MAX];
float cvt_vz[MAX];

float ec_tot_energy[MAX];
float ec_pcal_energy[MAX];
int ec_pcal_sec[MAX];
float ec_pcal_time[MAX];
float ec_pcal_path[MAX];
float ec_pcal_x[MAX];
float ec_pcal_y[MAX];
float ec_pcal_z[MAX];
float ec_pcal_lu[MAX];
float ec_pcal_lv[MAX];
float ec_pcal_lw[MAX];

float ec_ecin_energy[MAX];
int ec_ecin_sec[MAX];
float ec_ecin_time[MAX];
float ec_ecin_path[MAX];
float ec_ecin_x[MAX];
float ec_ecin_y[MAX];
float ec_ecin_z[MAX];
float ec_ecin_lu[MAX];
float ec_ecin_lv[MAX];
float ec_ecin_lw[MAX];

float ec_ecout_energy[MAX];
int ec_ecout_sec[MAX];
float ec_ecout_time[MAX];
float ec_ecout_path[MAX];
float ec_ecout_x[MAX];
float ec_ecout_y[MAX];
float ec_ecout_z[MAX];
float ec_ecout_lu[MAX];
float ec_ecout_lv[MAX];
float ec_ecout_lw[MAX];

float cc_nphe_tot[MAX];
int cc_ltcc_sec[MAX];
float cc_ltcc_nphe[MAX];
float cc_ltcc_time[MAX];
float cc_ltcc_path[MAX];
float cc_ltcc_theta[MAX];
float cc_ltcc_phi[MAX];
int cc_htcc_sec[MAX];
float cc_htcc_nphe[MAX];
float cc_htcc_time[MAX];
float cc_htcc_path[MAX];
float cc_htcc_theta[MAX];
float cc_htcc_phi[MAX];

int sc_ftof_sec[MAX];
float sc_ftof_time[MAX];
float sc_ftof_path[MAX];
float sc_ftof_layer[MAX];
float sc_ftof_energy[MAX];
float sc_ftof_x[MAX];
float sc_ftof_y[MAX];
float sc_ftof_z[MAX];
float sc_ftof_hx[MAX];
float sc_ftof_hy[MAX];
float sc_ftof_hz[MAX];

float sc_ctof_time[MAX];
float sc_ctof_path[MAX];
float sc_ctof_energy[MAX];
float sc_ctof_x[MAX];
float sc_ctof_y[MAX];
float sc_ctof_z[MAX];
float sc_ctof_hx[MAX];
float sc_ctof_hy[MAX];
float sc_ctof_hz[MAX];

float ft_cal_energy[MAX];
float ft_cal_time[MAX];
float ft_cal_path[MAX];
float ft_cal_x[MAX];
float ft_cal_y[MAX];
float ft_cal_z[MAX];
float ft_cal_dx[MAX];
float ft_cal_dy[MAX];
float ft_cal_radius[MAX];

float ft_hodo_energy[MAX];
float ft_hodo_time[MAX];
float ft_hodo_path[MAX];
float ft_hodo_x[MAX];
float ft_hodo_y[MAX];
float ft_hodo_z[MAX];
float ft_hodo_dx[MAX];
float ft_hodo_dy[MAX];
float ft_hodo_radius[MAX];

int main(int argc, char **argv) {
  auto start_full = std::chrono::high_resolution_clock::now();
  char InFileName[128];
  char OutFileName[128];

  if (argc == 2) {
    sprintf(InFileName, "%s", argv[1]);
    sprintf(OutFileName, "%s.root", argv[1]);
    std::cout << OutFileName << std::endl;
  } else if (argc == 3) {
    sprintf(InFileName, "%s", argv[1]);
    sprintf(OutFileName, "%s", argv[2]);
  } else {
    std::cout << "Please provide a filename to read...." << std::endl;
    exit(0);
  }
  TFile *OutputFile = new TFile(OutFileName, "RECREATE");
  OutputFile->SetCompressionSettings(9);
  TTree *clas12 = new TTree("clas12", "clas12");
  hipo::reader reader;
  reader.open(InFileName);

  hipo::node<int32_t> *run_node = reader.getBranch<int32_t>(11, 1);
  hipo::node<int32_t> *event_node = reader.getBranch<int32_t>(11, 2);
  hipo::node<float> *torus_node = reader.getBranch<float>(11, 8);
  hipo::node<float> *solenoid_node = reader.getBranch<float>(11, 9);
  hipo::node<int8_t> *crate_node = reader.getBranch<int8_t>(20013, 1);
  hipo::node<int8_t> *slot_node = reader.getBranch<int8_t>(20013, 2);
  hipo::node<int16_t> *channel_node = reader.getBranch<int16_t>(20013, 3);
  hipo::node<int8_t> *helicity_node = reader.getBranch<int8_t>(20013, 4);
  hipo::node<int8_t> *quartet_node = reader.getBranch<int8_t>(20013, 5);
  hipo::node<int32_t> *value_node = reader.getBranch<int32_t>(20013, 6);
  hipo::node<int32_t> *NRUN_node = reader.getBranch<int32_t>(330, 1);
  hipo::node<int32_t> *NEVENT_node = reader.getBranch<int32_t>(330, 2);
  hipo::node<float> *EVNTime_node = reader.getBranch<float>(330, 3);
  hipo::node<int8_t> *TYPE_node = reader.getBranch<int8_t>(330, 4);
  hipo::node<int64_t> *TRG_node = reader.getBranch<int64_t>(330, 7);
  hipo::node<float> *BCG_node = reader.getBranch<float>(330, 8);
  hipo::node<float> *STTime_node = reader.getBranch<float>(330, 10);
  hipo::node<float> *RFTime_node = reader.getBranch<float>(330, 11);
  hipo::node<int8_t> *Helic_node = reader.getBranch<int8_t>(330, 12);

  hipo::node<int32_t> *pid_node = reader.getBranch<int32_t>(331, 1);
  hipo::node<float> *px_node = reader.getBranch<float>(331, 2);
  hipo::node<float> *py_node = reader.getBranch<float>(331, 3);
  hipo::node<float> *pz_node = reader.getBranch<float>(331, 4);
  hipo::node<float> *vx_node = reader.getBranch<float>(331, 5);
  hipo::node<float> *vy_node = reader.getBranch<float>(331, 6);
  hipo::node<float> *vz_node = reader.getBranch<float>(331, 7);
  hipo::node<int8_t> *charge_node = reader.getBranch<int8_t>(331, 8);
  hipo::node<float> *beta_node = reader.getBranch<float>(331, 9);
  hipo::node<float> *chi2pid_node = reader.getBranch<float>(331, 10);
  hipo::node<int16_t> *status_node = reader.getBranch<int16_t>(331, 11);

  hipo::node<int16_t> *cal_pindex_node = reader.getBranch<int16_t>(332, 2);
  hipo::node<int8_t> *cal_detector_node = reader.getBranch<int8_t>(332, 3);
  hipo::node<int8_t> *cal_sector_node = reader.getBranch<int8_t>(332, 4);
  hipo::node<int8_t> *cal_layer_node = reader.getBranch<int8_t>(332, 5);
  hipo::node<float> *cal_energy_node = reader.getBranch<float>(332, 6);
  hipo::node<float> *cal_time_node = reader.getBranch<float>(332, 7);
  hipo::node<float> *cal_path_node = reader.getBranch<float>(332, 8);
  hipo::node<float> *cal_x_node = reader.getBranch<float>(332, 10);
  hipo::node<float> *cal_y_node = reader.getBranch<float>(332, 11);
  hipo::node<float> *cal_z_node = reader.getBranch<float>(332, 12);
  hipo::node<float> *cal_lu_node = reader.getBranch<float>(332, 16);
  hipo::node<float> *cal_lv_node = reader.getBranch<float>(332, 17);
  hipo::node<float> *cal_lw_node = reader.getBranch<float>(332, 18);

  hipo::node<int16_t> *chern_pindex_node = reader.getBranch<int16_t>(333, 2);
  hipo::node<int8_t> *chern_detector_node = reader.getBranch<int8_t>(333, 3);
  hipo::node<int8_t> *chern_sector_node = reader.getBranch<int8_t>(333, 4);
  hipo::node<float> *chern_nphe_node = reader.getBranch<float>(333, 5);
  hipo::node<float> *chern_time_node = reader.getBranch<float>(333, 6);
  hipo::node<float> *chern_path_node = reader.getBranch<float>(333, 7);
  hipo::node<float> *chern_theta_node = reader.getBranch<float>(333, 12);
  hipo::node<float> *chern_phi_node = reader.getBranch<float>(333, 13);

  hipo::node<int16_t> *fortag_pindex_node = reader.getBranch<int16_t>(334, 2);
  hipo::node<int8_t> *fortag_detector_node = reader.getBranch<int8_t>(334, 3);
  hipo::node<float> *fortag_energy_node = reader.getBranch<float>(334, 4);
  hipo::node<float> *fortag_time_node = reader.getBranch<float>(334, 5);
  hipo::node<float> *fortag_path_node = reader.getBranch<float>(334, 6);
  hipo::node<float> *fortag_x_node = reader.getBranch<float>(334, 8);
  hipo::node<float> *fortag_y_node = reader.getBranch<float>(334, 9);
  hipo::node<float> *fortag_z_node = reader.getBranch<float>(334, 10);
  hipo::node<float> *fortag_dx_node = reader.getBranch<float>(334, 11);
  hipo::node<float> *fortag_dy_node = reader.getBranch<float>(334, 12);
  hipo::node<float> *fortag_radius_node = reader.getBranch<float>(334, 13);
  hipo::node<int16_t> *fortag_size_node = reader.getBranch<int16_t>(334, 14);

  hipo::node<int16_t> *scint_pindex_node = reader.getBranch<int16_t>(335, 2);
  hipo::node<int8_t> *scint_detector_node = reader.getBranch<int8_t>(335, 3);
  hipo::node<int8_t> *scint_sector_node = reader.getBranch<int8_t>(335, 4);
  hipo::node<int8_t> *scint_layer_node = reader.getBranch<int8_t>(335, 5);
  hipo::node<int16_t> *scint_component_node = reader.getBranch<int16_t>(335, 6);
  hipo::node<float> *scint_energy_node = reader.getBranch<float>(335, 7);
  hipo::node<float> *scint_time_node = reader.getBranch<float>(335, 8);
  hipo::node<float> *scint_path_node = reader.getBranch<float>(335, 9);

  hipo::node<int16_t> *track_pindex_node = reader.getBranch<int16_t>(336, 2);
  hipo::node<int8_t> *track_detector_node = reader.getBranch<int8_t>(336, 3);
  hipo::node<int8_t> *track_sector_node = reader.getBranch<int8_t>(336, 4);
  hipo::node<float> *track_px_nomm_node = reader.getBranch<float>(336, 9);
  hipo::node<float> *track_py_nomm_node = reader.getBranch<float>(336, 10);
  hipo::node<float> *track_pz_nomm_node = reader.getBranch<float>(336, 11);
  hipo::node<float> *track_vx_nomm_node = reader.getBranch<float>(336, 12);
  hipo::node<float> *track_vy_nomm_node = reader.getBranch<float>(336, 13);
  hipo::node<float> *track_vz_nomm_node = reader.getBranch<float>(336, 14);

  clas12->Branch("run", &run, "run/I");
  clas12->Branch("event", &event, "event/I");
  clas12->Branch("torus", &torus, "torus/F");
  clas12->Branch("solenoid", &solenoid, "solenoid/F");

  clas12->Branch("nCrate", &nCrate);
  clas12->Branch("crate", crate);
  clas12->Branch("slot", slot);
  clas12->Branch("channel", channel);
  clas12->Branch("helicity", helicity);
  clas12->Branch("quartet", quartet);
  clas12->Branch("value", value);

  clas12->Branch("nTime", &nTime);
  clas12->Branch("STTime", STTime);
  clas12->Branch("RFTime", RFTime);

  clas12->Branch("gpart", &gpart);
  clas12->Branch("pid", pid, "pid[gpart]/I");
  clas12->Branch("p", p, "p[gpart]/F");
  clas12->Branch("p2", p2, "p2[gpart]/F");
  clas12->Branch("px", px, "px[gpart]/F");
  clas12->Branch("py", py, "py[gpart]/F");
  clas12->Branch("pz", pz, "pz[gpart]/F");
  clas12->Branch("vx", vx, "vx[gpart]/F");
  clas12->Branch("vy", vy, "vy[gpart]/F");
  clas12->Branch("vz", vz, "vz[gpart]/F");
  clas12->Branch("charge", charge, "charge[gpart]/F");
  clas12->Branch("beta", beta, "beta[gpart]/F");
  clas12->Branch("chi2pid", chi2pid, "chi2pid[gpart]/F");
  clas12->Branch("status", status, "status[gpart]/F");

  clas12->Branch("ec_tot_energy", ec_tot_energy, "ec_tot_energy[gpart]/F");
  clas12->Branch("ec_pcal_energy", ec_pcal_energy, "ec_pcal_energy[gpart]/F");
  clas12->Branch("ec_pcal_sec", ec_pcal_sec, "ec_pcal_sec[gpart]/I");
  clas12->Branch("ec_pcal_time", ec_pcal_time, "ec_pcal_time[gpart]/F");
  clas12->Branch("ec_pcal_path", ec_pcal_path, "ec_pcal_path[gpart]/F");
  clas12->Branch("ec_pcal_x", ec_pcal_x, "ec_pcal_x[gpart]/F");
  clas12->Branch("ec_pcal_y", ec_pcal_y, "ec_pcal_y[gpart]/F");
  clas12->Branch("ec_pcal_z", ec_pcal_z, "ec_pcal_z[gpart]/F");
  clas12->Branch("ec_pcal_lu", ec_pcal_lu, "ec_pcal_lu[gpart]/F");
  clas12->Branch("ec_pcal_lv", ec_pcal_lv, "ec_pcal_lv[gpart]/F");
  clas12->Branch("ec_pcal_lw", ec_pcal_lw, "ec_pcal_lw[gpart]/F");

  clas12->Branch("ec_ecin_energy", ec_ecin_energy, "ec_ecin_energy[gpart]/F");
  clas12->Branch("ec_ecin_sec", ec_ecin_sec, "ec_ecin_sec[gpart]/I");
  clas12->Branch("ec_ecin_time", ec_ecin_time, "ec_ecin_time[gpart]/F");
  clas12->Branch("ec_ecin_path", ec_ecin_path, "ec_ecin_path[gpart]/F");
  clas12->Branch("ec_ecin_x", ec_ecin_x, "ec_ecin_x[gpart]/F");
  clas12->Branch("ec_ecin_y", ec_ecin_y, "ec_ecin_y[gpart]/F");
  clas12->Branch("ec_ecin_z", ec_ecin_z, "ec_ecin_z[gpart]/F");
  clas12->Branch("ec_ecin_lu", ec_ecin_lu, "ec_ecin_lu[gpart]/F");
  clas12->Branch("ec_ecin_lv", ec_ecin_lv, "ec_ecin_lv[gpart]/F");
  clas12->Branch("ec_ecin_lw", ec_ecin_lw, "ec_ecin_lw[gpart]/F");

  clas12->Branch("ec_ecout_energy", ec_ecout_energy, "ec_ecout_energy[gpart]/F");
  clas12->Branch("ec_ecout_sec", ec_ecout_sec, "ec_ecout_sec[gpart]/I");
  clas12->Branch("ec_ecout_time", ec_ecout_time, "ec_ecout_time[gpart]/F");
  clas12->Branch("ec_ecout_path", ec_ecout_path, "ec_ecout_path[gpart]/F");
  clas12->Branch("ec_ecout_x", ec_ecout_x, "ec_ecout_x[gpart]/F");
  clas12->Branch("ec_ecout_y", ec_ecout_y, "ec_ecout_y[gpart]/F");
  clas12->Branch("ec_ecout_z", ec_ecout_z, "ec_ecout_z[gpart]/F");
  clas12->Branch("ec_ecout_lu", ec_ecout_lu, "ec_ecout_lu[gpart]/F");
  clas12->Branch("ec_ecout_lv", ec_ecout_lv, "ec_ecout_lv[gpart]/F");
  clas12->Branch("ec_ecout_lw", ec_ecout_lw, "ec_ecout_lw[gpart]/F");

  clas12->Branch("dc_sec", dc_sec, "dc_sec[gpart]/I");
  clas12->Branch("dc_px", dc_px, "dc_px[gpart]/F");
  clas12->Branch("dc_py", dc_py, "dc_py[gpart]/F");
  clas12->Branch("dc_pz", dc_pz, "dc_pz[gpart]/F");
  clas12->Branch("dc_vx", dc_vx, "dc_vx[gpart]/F");
  clas12->Branch("dc_vy", dc_vy, "dc_vy[gpart]/F");
  clas12->Branch("dc_vz", dc_vz, "dc_vz[gpart]/F");

  clas12->Branch("cvt_px", cvt_px, "cvt_px[gpart]/F");
  clas12->Branch("cvt_py", cvt_py, "cvt_py[gpart]/F");
  clas12->Branch("cvt_pz", cvt_pz, "cvt_pz[gpart]/F");
  clas12->Branch("cvt_vx", cvt_vx, "cvt_vx[gpart]/F");
  clas12->Branch("cvt_vy", cvt_vy, "cvt_vy[gpart]/F");
  clas12->Branch("cvt_vz", cvt_vz, "cvt_vz[gpart]/F");

  clas12->Branch("cc_nphe_tot", cc_nphe_tot, "cc_nphe_tot[gpart]/F");
  clas12->Branch("cc_ltcc_sec", cc_ltcc_sec, "cc_ltcc_sec[gpart]/I");
  clas12->Branch("cc_ltcc_nphe", cc_ltcc_nphe, "cc_ltcc_nphe[gpart]/F");
  clas12->Branch("cc_ltcc_time", cc_ltcc_time, "cc_ltcc_time[gpart]/F");
  clas12->Branch("cc_ltcc_path", cc_ltcc_path, "cc_ltcc_path[gpart]/F");
  clas12->Branch("cc_ltcc_theta", cc_ltcc_theta, "cc_ltcc_theta[gpart]/F");
  clas12->Branch("cc_ltcc_phi", cc_ltcc_phi, "cc_ltcc_phi[gpart]/F");

  clas12->Branch("cc_htcc_sec", cc_htcc_sec, "cc_htcc_sec[gpart]/I");
  clas12->Branch("cc_htcc_nphe", cc_htcc_nphe, "cc_htcc_nphe[gpart]/F");
  clas12->Branch("cc_htcc_time", cc_htcc_time, "cc_htcc_time[gpart]/F");
  clas12->Branch("cc_htcc_path", cc_htcc_path, "cc_htcc_path[gpart]/F");
  clas12->Branch("cc_htcc_theta", cc_htcc_theta, "cc_htcc_theta[gpart]/F");
  clas12->Branch("cc_htcc_phi", cc_htcc_phi, "cc_htcc_phi[gpart]/F");

  clas12->Branch("sc_ftof_sec", sc_ftof_sec, "sc_ftof_sec[gpart]/I");
  clas12->Branch("sc_ftof_time", sc_ftof_time, "sc_ftof_time[gpart]/F");
  clas12->Branch("sc_ftof_path", sc_ftof_path, "sc_ftof_path[gpart]/F");
  clas12->Branch("sc_ftof_layer", sc_ftof_layer, "sc_ftof_layer[gpart]/F");

  clas12->Branch("sc_ftof_energy", sc_ftof_energy, "sc_ftof_energy[gpart]/F");
  clas12->Branch("sc_ctof_time", sc_ctof_time, "sc_ctof_time[gpart]/F");
  clas12->Branch("sc_ctof_path", sc_ctof_path, "sc_ctof_path[gpart]/F");
  clas12->Branch("sc_ctof_energy", sc_ctof_energy, "sc_ctof_energy[gpart]/F");

  clas12->Branch("ft_cal_energy", ft_cal_energy, "ft_cal_energy[gpart]/F");
  clas12->Branch("ft_cal_time", ft_cal_time, "ft_cal_time[gpart]/F");
  clas12->Branch("ft_cal_path", ft_cal_path, "ft_cal_path[gpart]/F");
  clas12->Branch("ft_cal_x", ft_cal_x, "ft_cal_x[gpart]/F");
  clas12->Branch("ft_cal_y", ft_cal_y, "ft_cal_y[gpart]/F");
  clas12->Branch("ft_cal_z", ft_cal_z, "ft_cal_z[gpart]/F");
  clas12->Branch("ft_cal_dx", ft_cal_dx, "ft_cal_dx[gpart]/F");
  clas12->Branch("ft_cal_dy", ft_cal_dy, "ft_cal_dy[gpart]/F");
  clas12->Branch("ft_cal_radius", ft_cal_radius, "ft_cal_radius[gpart]/F");

  clas12->Branch("ft_hodo_energy", ft_hodo_energy, "ft_hodo_energy[gpart]/F");
  clas12->Branch("ft_hodo_time", ft_hodo_time, "ft_hodo_time[gpart]/F");
  clas12->Branch("ft_hodo_path", ft_hodo_path, "ft_hodo_path[gpart]/F");
  clas12->Branch("ft_hodo_x", ft_hodo_x, "ft_hodo_x[gpart]/F");
  clas12->Branch("ft_hodo_y", ft_hodo_y, "ft_hodo_y[gpart]/F");
  clas12->Branch("ft_hodo_z", ft_hodo_z, "ft_hodo_z[gpart]/F");
  clas12->Branch("ft_hodo_dx", ft_hodo_dx, "ft_hodo_dx[gpart]/F");
  clas12->Branch("ft_hodo_dy", ft_hodo_dy, "ft_hodo_dy[gpart]/F");
  clas12->Branch("ft_hodo_radius", ft_hodo_radius, "ft_hodo_radius[gpart]/F");

  int entry = 0;
  int l = 0;
  int len_pindex = 0;
  while (reader.next() == true) {
    entry++;
    if ((entry % 1000) == 0) std::cerr << "\t" << entry << "\r\r" << std::flush;

    // if (pid_node->getLength() == 0) continue;

    run = run_node->getValue(0);
    event = event_node->getValue(0);
    torus = torus_node->getValue(0);
    solenoid = solenoid_node->getValue(0);

    nCrate = crate_node->getLength();
    for (int i = 0; i < nCrate; i++) {
      crate[i] = crate_node->getValue(i);
      slot[i] = slot_node->getValue(i);
      channel[i] = channel_node->getValue(i);
      helicity[i] = helicity_node->getValue(i);
      quartet[i] = quartet_node->getValue(i);
      value[i] = value_node->getValue(i);
    }

    nTime = STTime_node->getLength();
    for (int i = 0; i < nTime; i++) {
      STTime[i] = STTime_node->getValue(i);
      RFTime[i] = RFTime_node->getValue(i);
    }

    gpart = pid_node->getLength();
    for (int i = 0; i < gpart; i++) {
      pid[i] = pid_node->getValue(i);
      p2[i] = (px_node->getValue(i) * px_node->getValue(i) + py_node->getValue(i) * py_node->getValue(i) +
               pz_node->getValue(i) * pz_node->getValue(i));
      p[i] = sqrt(p2[i]);
      px[i] = px_node->getValue(i);
      py[i] = py_node->getValue(i);
      pz[i] = pz_node->getValue(i);
      vx[i] = vx_node->getValue(i);
      vy[i] = vy_node->getValue(i);
      vz[i] = vz_node->getValue(i);
      charge[i] = charge_node->getValue(i);
      beta[i] = ((beta_node->getValue(i) != -9999) ? beta_node->getValue(i) : NaN);
      chi2pid[i] = chi2pid_node->getValue(i);
      status[i] = status_node->getValue(i);
    }

    for (int i = 0; i < gpart; i++) {
      ec_tot_energy[i] = NaN;
      ec_pcal_energy[i] = NaN;
      ec_pcal_sec[i] = -1;
      ec_pcal_time[i] = NaN;
      ec_pcal_path[i] = NaN;
      ec_pcal_x[i] = NaN;
      ec_pcal_y[i] = NaN;
      ec_pcal_z[i] = NaN;
      ec_pcal_lu[i] = NaN;
      ec_pcal_lv[i] = NaN;
      ec_pcal_lw[i] = NaN;
      ec_ecin_energy[i] = NaN;
      ec_ecin_sec[i] = -1;
      ec_ecin_time[i] = NaN;
      ec_ecin_path[i] = NaN;
      ec_ecin_x[i] = NaN;
      ec_ecin_y[i] = NaN;
      ec_ecin_z[i] = NaN;
      ec_ecin_lu[i] = NaN;
      ec_ecin_lv[i] = NaN;
      ec_ecin_lw[i] = NaN;
      ec_ecout_energy[i] = NaN;
      ec_ecout_sec[i] = -1;
      ec_ecout_time[i] = NaN;
      ec_ecout_path[i] = NaN;
      ec_ecout_x[i] = NaN;
      ec_ecout_y[i] = NaN;
      ec_ecout_z[i] = NaN;
      ec_ecout_lu[i] = NaN;
      ec_ecout_lv[i] = NaN;
      ec_ecout_lw[i] = NaN;
      cc_nphe_tot[i] = NaN;
      cc_ltcc_sec[i] = -1;
      cc_ltcc_nphe[i] = NaN;
      cc_ltcc_time[i] = NaN;
      cc_ltcc_path[i] = NaN;
      cc_ltcc_theta[i] = NaN;
      cc_ltcc_phi[i] = NaN;
      cc_htcc_sec[i] = -1;
      cc_htcc_nphe[i] = NaN;
      cc_htcc_time[i] = NaN;
      cc_htcc_path[i] = NaN;
      cc_htcc_theta[i] = NaN;
      cc_htcc_phi[i] = NaN;
      sc_ftof_sec[i] = -1;
      sc_ftof_time[i] = NaN;
      sc_ftof_path[i] = NaN;
      sc_ftof_layer[i] = NaN;
      sc_ftof_energy[i] = NaN;
      sc_ctof_time[i] = NaN;
      sc_ctof_path[i] = NaN;
      sc_ctof_energy[i] = NaN;
      dc_sec[i] = -1;
      dc_px[i] = NaN;
      dc_py[i] = NaN;
      dc_pz[i] = NaN;
      dc_vx[i] = NaN;
      dc_vy[i] = NaN;
      dc_vz[i] = NaN;
      cvt_px[i] = NaN;
      cvt_py[i] = NaN;
      cvt_pz[i] = NaN;
      cvt_vx[i] = NaN;
      cvt_vy[i] = NaN;
      cvt_vz[i] = NaN;
      ft_cal_energy[i] = NaN;
      ft_cal_time[i] = NaN;
      ft_cal_path[i] = NaN;
      ft_cal_x[i] = NaN;
      ft_cal_y[i] = NaN;
      ft_cal_z[i] = NaN;
      ft_cal_dx[i] = NaN;
      ft_cal_dy[i] = NaN;
      ft_cal_radius[i] = NaN;
      ft_hodo_energy[i] = NaN;
      ft_hodo_time[i] = NaN;
      ft_hodo_path[i] = NaN;
      ft_hodo_x[i] = NaN;
      ft_hodo_y[i] = NaN;
      ft_hodo_z[i] = NaN;
      ft_hodo_dx[i] = NaN;
      ft_hodo_dy[i] = NaN;
      ft_hodo_radius[i] = NaN;
    }

    float pcal = 0.0;
    float einner = 0.0;
    float eouter = 0.0;
    float etot = 0.0;

    for (int i = 0; i < gpart; i++) {
      for (int k = 0; k < cal_pindex_node->getLength(); k++) {
        int pindex = cal_pindex_node->getValue(k);
        int detector = cal_detector_node->getValue(k);

        int _pcal_sec = -1;
        float _pcal_t = NaN;
        float _pcal_r = NaN;
        float _pcal_x = NaN;
        float _pcal_y = NaN;
        float _pcal_z = NaN;
        float _pcal_lu = NaN;
        float _pcal_lv = NaN;
        float _pcal_lw = NaN;

        int _ecin_sec = -1;
        float _ecin_t = NaN;
        float _ecin_r = NaN;
        float _ecin_x = NaN;
        float _ecin_y = NaN;
        float _ecin_z = NaN;
        float _ecin_lu = NaN;
        float _ecin_lv = NaN;
        float _ecin_lw = NaN;

        int _ecout_sec = -1;
        float _ecout_t = NaN;
        float _ecout_r = NaN;
        float _ecout_x = NaN;
        float _ecout_y = NaN;
        float _ecout_z = NaN;
        float _ecout_lu = NaN;
        float _ecout_lv = NaN;
        float _ecout_lw = NaN;

        if (pindex == i && detector == 7) {
          int layer = cal_layer_node->getValue(k);
          float energy = cal_energy_node->getValue(k);
          etot += energy;
          if (layer == 1) {
            pcal += energy;
            _pcal_sec = cal_sector_node->getValue(k);
            _pcal_t = cal_time_node->getValue(k);
            _pcal_r = cal_path_node->getValue(k);
            _pcal_x = cal_x_node->getValue(k);
            _pcal_y = cal_y_node->getValue(k);
            _pcal_z = cal_z_node->getValue(k);
            _pcal_lu = cal_lu_node->getValue(k);
            _pcal_lv = cal_lv_node->getValue(k);
            _pcal_lw = cal_lw_node->getValue(k);
          } else if (layer == 4) {
            einner += energy;
            _ecin_sec = cal_sector_node->getValue(k);
            _ecin_t = cal_time_node->getValue(k);
            _ecin_r = cal_path_node->getValue(k);
            _ecin_x = cal_x_node->getValue(k);
            _ecin_y = cal_y_node->getValue(k);
            _ecin_z = cal_z_node->getValue(k);
            _ecin_lu = cal_lu_node->getValue(k);
            _ecin_lv = cal_lv_node->getValue(k);
            _ecin_lw = cal_lw_node->getValue(k);
          } else if (layer == 7) {
            eouter += energy;
            _ecout_sec = cal_sector_node->getValue(k);
            _ecout_t = cal_time_node->getValue(k);
            _ecout_r = cal_path_node->getValue(k);
            _ecout_x = cal_x_node->getValue(k);
            _ecout_y = cal_y_node->getValue(k);
            _ecout_z = cal_z_node->getValue(k);
            _ecout_lu = cal_lu_node->getValue(k);
            _ecout_lv = cal_lv_node->getValue(k);
            _ecout_lw = cal_lw_node->getValue(k);
          }
        }

        if (ec_pcal_sec[i] == -1) ec_pcal_sec[i] = _pcal_sec;
        if (ec_pcal_time[i] != ec_pcal_time[i]) ec_pcal_time[i] = _pcal_t;
        if (ec_pcal_path[i] != ec_pcal_path[i]) ec_pcal_path[i] = _pcal_r;
        if (ec_pcal_x[i] != ec_pcal_x[i]) ec_pcal_x[i] = _pcal_x;
        if (ec_pcal_y[i] != ec_pcal_y[i]) ec_pcal_y[i] = _pcal_y;
        if (ec_pcal_z[i] != ec_pcal_z[i]) ec_pcal_z[i] = _pcal_z;
        if (ec_pcal_lu[i] != ec_pcal_lu[i]) ec_pcal_lu[i] = _pcal_lu;
        if (ec_pcal_lv[i] != ec_pcal_lv[i]) ec_pcal_lv[i] = _pcal_lv;
        if (ec_pcal_lw[i] != ec_pcal_lw[i]) ec_pcal_lw[i] = _pcal_lw;

        if (ec_ecin_sec[i] == -1) ec_ecin_sec[i] = _ecin_sec;
        if (ec_ecin_time[i] != ec_ecin_time[i]) ec_ecin_time[i] = _ecin_t;
        if (ec_ecin_path[i] != ec_ecin_path[i]) ec_ecin_path[i] = _ecin_r;
        if (ec_ecin_x[i] != ec_ecin_x[i]) ec_ecin_x[i] = _ecin_x;
        if (ec_ecin_y[i] != ec_ecin_y[i]) ec_ecin_y[i] = _ecin_y;
        if (ec_ecin_z[i] != ec_ecin_z[i]) ec_ecin_z[i] = _ecin_z;
        if (ec_ecin_lu[i] != ec_ecin_lu[i]) ec_ecin_lu[i] = _ecin_lu;
        if (ec_ecin_lv[i] != ec_ecin_lv[i]) ec_ecin_lv[i] = _ecin_lv;
        if (ec_ecin_lw[i] != ec_ecin_lw[i]) ec_ecin_lw[i] = _ecin_lw;

        if (ec_ecout_sec[i] == -1) ec_ecout_sec[i] = _ecout_sec;
        if (ec_ecout_time[i] != ec_ecout_time[i]) ec_ecout_time[i] = _ecout_t;
        if (ec_ecout_path[i] != ec_ecout_path[i]) ec_ecout_path[i] = _ecout_r;
        if (ec_ecout_x[i] != ec_ecout_x[i]) ec_ecout_x[i] = _ecout_x;
        if (ec_ecout_y[i] != ec_ecout_y[i]) ec_ecout_y[i] = _ecout_y;
        if (ec_ecout_z[i] != ec_ecout_z[i]) ec_ecout_z[i] = _ecout_z;
        if (ec_ecout_lu[i] != ec_ecout_lu[i]) ec_ecout_lu[i] = _ecout_lu;
        if (ec_ecout_lv[i] != ec_ecout_lv[i]) ec_ecout_lv[i] = _ecout_lv;
        if (ec_ecout_lw[i] != ec_ecout_lw[i]) ec_ecout_lw[i] = _ecout_lw;
      }
      if (ec_pcal_energy[i] != ec_pcal_energy[i]) ec_pcal_energy[i] = ((pcal != 0.0) ? pcal : NaN);
      if (ec_ecin_energy[i] != ec_ecin_energy[i]) ec_ecin_energy[i] = ((einner != 0.0) ? einner : NaN);
      if (ec_ecout_energy[i] != ec_ecout_energy[i]) ec_ecout_energy[i] = ((eouter != 0.0) ? eouter : NaN);
      if (ec_tot_energy[i] != ec_tot_energy[i]) ec_tot_energy[i] = ((etot != 0.0) ? etot : NaN);

      float nphe_tot = 0.0;

      for (int k = 0; k < chern_pindex_node->getLength(); k++) {
        int pindex = chern_pindex_node->getValue(k);
        int detector = chern_detector_node->getValue(k);

        int _ltcc_sec = -1;
        float _ltcc_t = NaN;
        float _ltcc_r = NaN;
        float _ltcc_theta = NaN;
        float _ltcc_phi = NaN;
        float _ltcc_nphe = NaN;

        int _htcc_sec = -1;
        float _htcc_t = NaN;
        float _htcc_r = NaN;
        float _htcc_theta = NaN;
        float _htcc_phi = NaN;
        float _htcc_nphe = NaN;
        if (pindex == i && (detector == 15 || detector == 16)) nphe_tot += chern_nphe_node->getValue(k);

        if (pindex == i && detector == 15) {
          _htcc_sec = chern_sector_node->getValue(k);
          _htcc_t = chern_time_node->getValue(k);
          _htcc_r = chern_path_node->getValue(k);
          _htcc_theta = chern_theta_node->getValue(k);
          _htcc_phi = chern_phi_node->getValue(k);
          _htcc_nphe = chern_nphe_node->getValue(k);
        } else if (pindex == i && detector == 16) {
          _ltcc_sec = chern_sector_node->getValue(k);
          _ltcc_t = chern_time_node->getValue(k);
          _ltcc_r = chern_path_node->getValue(k);
          _ltcc_theta = chern_theta_node->getValue(k);
          _ltcc_phi = chern_phi_node->getValue(k);
          _ltcc_nphe = chern_nphe_node->getValue(k);
        }

        if (cc_htcc_sec[i] == -1) cc_htcc_sec[i] = _htcc_sec;
        if (cc_htcc_time[i] != cc_htcc_time[i]) cc_htcc_time[i] = _htcc_t;
        if (cc_htcc_path[i] != cc_htcc_path[i]) cc_htcc_path[i] = _htcc_r;
        if (cc_htcc_theta[i] != cc_htcc_theta[i]) cc_htcc_theta[i] = _htcc_theta;
        if (cc_htcc_phi[i] != cc_htcc_phi[i]) cc_htcc_phi[i] = _htcc_phi;
        if (cc_htcc_nphe[i] != cc_htcc_nphe[i]) cc_htcc_nphe[i] = _htcc_nphe;

        if (cc_ltcc_sec[i] == -1) cc_ltcc_sec[i] = _ltcc_sec;
        if (cc_ltcc_time[i] != cc_ltcc_time[i]) cc_ltcc_time[i] = _ltcc_t;
        if (cc_ltcc_path[i] != cc_ltcc_path[i]) cc_ltcc_path[i] = _ltcc_r;
        if (cc_ltcc_theta[i] != cc_ltcc_theta[i]) cc_ltcc_theta[i] = _ltcc_theta;
        if (cc_ltcc_phi[i] != cc_ltcc_phi[i]) cc_ltcc_phi[i] = _ltcc_phi;
        if (cc_ltcc_nphe[i] != cc_ltcc_nphe[i]) cc_ltcc_nphe[i] = _ltcc_nphe;
      }
      if (cc_nphe_tot[i] != cc_nphe_tot[i]) cc_nphe_tot[i] = ((nphe_tot != 0.0) ? nphe_tot : NaN);

      for (int k = 0; k < scint_pindex_node->getLength(); k++) {
        int pindex = scint_pindex_node->getValue(k);
        int detector = scint_detector_node->getValue(k);

        int _sc_ftof_sec = -1;
        float _sc_ftof_time = NaN;
        float _sc_ftof_path = NaN;
        float _sc_ftof_layer = NaN;
        float _sc_ftof_energy = NaN;

        float _sc_ctof_time = NaN;
        float _sc_ctof_path = NaN;
        float _sc_ctof_energy = NaN;

        if (pindex == i && detector == 12) {
          _sc_ftof_sec = scint_sector_node->getValue(k);
          _sc_ftof_time = scint_time_node->getValue(k);
          _sc_ftof_path = scint_path_node->getValue(k);
          _sc_ftof_layer = scint_layer_node->getValue(k);
          _sc_ftof_energy = scint_energy_node->getValue(k);

        } else if (pindex == i && detector == 4) {
          _sc_ctof_time = scint_time_node->getValue(k);
          _sc_ctof_path = scint_path_node->getValue(k);
          _sc_ctof_energy = scint_energy_node->getValue(k);
        }
        if (sc_ftof_sec[i] == -1) sc_ftof_sec[i] = _sc_ftof_sec;
        if (sc_ftof_time[i] != sc_ftof_time[i]) sc_ftof_time[i] = _sc_ftof_time;
        if (sc_ftof_path[i] != sc_ftof_path[i]) sc_ftof_path[i] = _sc_ftof_path;
        if (sc_ftof_layer[i] != sc_ftof_layer[i]) sc_ftof_layer[i] = _sc_ftof_layer;
        if (sc_ftof_energy[i] != sc_ftof_energy[i]) sc_ftof_energy[i] = _sc_ftof_energy;
        if (sc_ctof_time[i] != sc_ctof_time[i]) sc_ctof_time[i] = _sc_ctof_time;
        if (sc_ctof_path[i] != sc_ctof_path[i]) sc_ctof_path[i] = _sc_ctof_path;
        if (sc_ctof_energy[i] != sc_ctof_energy[i]) sc_ctof_energy[i] = _sc_ctof_energy;
      }

      for (int k = 0; k < track_pindex_node->getLength(); k++) {
        int pindex = track_pindex_node->getValue(k);
        int detector = track_detector_node->getValue(k);

        int _dc_sec = -1;
        float _dc_px = NaN;
        float _dc_py = NaN;
        float _dc_pz = NaN;
        float _dc_vx = NaN;
        float _dc_vy = NaN;
        float _dc_vz = NaN;

        float _cvt_px = NaN;
        float _cvt_py = NaN;
        float _cvt_pz = NaN;
        float _cvt_vx = NaN;
        float _cvt_vy = NaN;
        float _cvt_vz = NaN;

        if (pindex == i && detector == 5) {
          cvt_px[i] = track_px_nomm_node->getValue(k);
          cvt_py[i] = track_py_nomm_node->getValue(k);
          cvt_pz[i] = track_pz_nomm_node->getValue(k);
          cvt_vx[i] = track_vx_nomm_node->getValue(k);
          cvt_vy[i] = track_vy_nomm_node->getValue(k);
          cvt_vz[i] = track_vz_nomm_node->getValue(k);

        } else if (pindex == i && detector == 6) {
          _dc_sec = track_sector_node->getValue(k);
          _dc_px = track_px_nomm_node->getValue(k);
          _dc_py = track_py_nomm_node->getValue(k);
          _dc_pz = track_pz_nomm_node->getValue(k);
          _dc_vx = track_vx_nomm_node->getValue(k);
          _dc_vy = track_vy_nomm_node->getValue(k);
          _dc_vz = track_vz_nomm_node->getValue(k);
        }

        if (dc_sec[i] == -1) dc_sec[i] = _dc_sec;
        if (dc_px[i] != dc_px[i]) dc_px[i] = _dc_px;
        if (dc_py[i] != dc_py[i]) dc_py[i] = _dc_py;
        if (dc_pz[i] != dc_pz[i]) dc_pz[i] = _dc_pz;
        if (dc_vx[i] != dc_vx[i]) dc_vx[i] = _dc_vx;
        if (dc_vy[i] != dc_vy[i]) dc_vy[i] = _dc_vy;
        if (dc_vz[i] != dc_vz[i]) dc_vz[i] = _dc_vz;

        if (cvt_px[i] != cvt_px[i]) cvt_px[i] = _cvt_px;
        if (cvt_py[i] != cvt_py[i]) cvt_py[i] = _cvt_py;
        if (cvt_pz[i] != cvt_pz[i]) cvt_pz[i] = _cvt_pz;
        if (cvt_vx[i] != cvt_vx[i]) cvt_vx[i] = _cvt_vx;
        if (cvt_vy[i] != cvt_vy[i]) cvt_vy[i] = _cvt_vy;
        if (cvt_vz[i] != cvt_vz[i]) cvt_vz[i] = _cvt_vz;
      }

      for (int k = 0; k < fortag_pindex_node->getLength(); k++) {
        int pindex = fortag_pindex_node->getValue(k);
        int detector = fortag_detector_node->getValue(k);

        float _cal_energy = NaN;
        float _cal_time = NaN;
        float _cal_path = NaN;
        float _cal_x = NaN;
        float _cal_y = NaN;
        float _cal_z = NaN;
        float _cal_dx = NaN;
        float _cal_dy = NaN;
        float _cal_radius = NaN;

        float _hodo_energy = NaN;
        float _hodo_time = NaN;
        float _hodo_path = NaN;
        float _hodo_x = NaN;
        float _hodo_y = NaN;
        float _hodo_z = NaN;
        float _hodo_dx = NaN;
        float _hodo_dy = NaN;
        float _hodo_radius = NaN;

        if (pindex == i && detector == 10 && detector != 11) {
          _cal_energy = fortag_energy_node->getValue(k);
          _cal_time = fortag_time_node->getValue(k);
          _cal_path = fortag_path_node->getValue(k);
          _cal_x = fortag_x_node->getValue(k);
          _cal_y = fortag_y_node->getValue(k);
          _cal_z = fortag_z_node->getValue(k);
          _cal_dx = fortag_dx_node->getValue(k);
          _cal_dy = fortag_dy_node->getValue(k);
          _cal_radius = fortag_radius_node->getValue(k);
        } else if (pindex == i && detector == 11) {
          _hodo_energy = fortag_energy_node->getValue(k);
          _hodo_time = fortag_time_node->getValue(k);
          _hodo_path = fortag_path_node->getValue(k);
          _hodo_x = fortag_x_node->getValue(k);
          _hodo_y = fortag_y_node->getValue(k);
          _hodo_z = fortag_z_node->getValue(k);
          _hodo_dx = fortag_dx_node->getValue(k);
          _hodo_dy = fortag_dy_node->getValue(k);
          _hodo_radius = fortag_radius_node->getValue(k);
        }

        if (ft_cal_energy[i] != ft_cal_energy[i]) ft_cal_energy[i] = _cal_energy;
        if (ft_cal_time[i] != ft_cal_time[i]) ft_cal_time[i] = _cal_time;
        if (ft_cal_path[i] != ft_cal_path[i]) ft_cal_path[i] = _cal_path;
        if (ft_cal_x[i] != ft_cal_x[i]) ft_cal_x[i] = _cal_x;
        if (ft_cal_y[i] != ft_cal_y[i]) ft_cal_y[i] = _cal_y;
        if (ft_cal_z[i] != ft_cal_z[i]) ft_cal_z[i] = _cal_z;
        if (ft_cal_dx[i] != ft_cal_dx[i]) ft_cal_dx[i] = _cal_dx;
        if (ft_cal_dy[i] != ft_cal_dy[i]) ft_cal_dy[i] = _cal_dy;
        if (ft_cal_radius[i] != ft_cal_radius[i]) ft_cal_radius[i] = _cal_radius;

        if (ft_hodo_energy[i] != ft_hodo_energy[i]) ft_hodo_energy[i] = _hodo_energy;
        if (ft_hodo_time[i] != ft_hodo_time[i]) ft_hodo_time[i] = _hodo_time;
        if (ft_hodo_path[i] != ft_hodo_path[i]) ft_hodo_path[i] = _hodo_path;
        if (ft_hodo_x[i] != ft_hodo_x[i]) ft_hodo_x[i] = _hodo_x;
        if (ft_hodo_y[i] != ft_hodo_y[i]) ft_hodo_y[i] = _hodo_y;
        if (ft_hodo_z[i] != ft_hodo_z[i]) ft_hodo_z[i] = _hodo_z;
        if (ft_hodo_dx[i] != ft_hodo_dx[i]) ft_hodo_dx[i] = _hodo_dx;
        if (ft_hodo_dy[i] != ft_hodo_dy[i]) ft_hodo_dy[i] = _hodo_dy;
        if (ft_hodo_radius[i] != ft_hodo_radius[i]) ft_hodo_radius[i] = _hodo_radius;
      }
    }

    clas12->Fill();
  }

  OutputFile->cd();
  clas12->Write();
  OutputFile->Write();

  reader.close();
  std::chrono::duration<double> elapsed_full = (std::chrono::high_resolution_clock::now() - start_full);
  std::cout << "Elapsed time: " << elapsed_full.count() << " s" << std::endl;
  std::cout << "Events/Sec: " << entry / elapsed_full.count() << " Hz" << std::endl;

  return 0;
}
