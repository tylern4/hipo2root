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

  std::vector<int> run_vec;
  std::vector<int> event_vec;
  std::vector<float> torus_vec;
  std::vector<float> solenoid_vec;
  std::vector<int> crate_vec;
  std::vector<int> slot_vec;
  std::vector<int> channel_vec;
  std::vector<int> helicity_vec;
  std::vector<int> quartet_vec;
  std::vector<int> value_vec;
  std::vector<int> NRUN_vec;
  std::vector<int> NEVENT_vec;
  std::vector<float> EVNTime_vec;
  std::vector<int> TYPE_vec;
  std::vector<int> TRG_vec;
  std::vector<float> BCG_vec;
  std::vector<float> STTime_vec;
  std::vector<float> RFTime_vec;
  std::vector<int> Helic_vec;

  std::vector<int> pid_vec;
  std::vector<float> px_vec;
  std::vector<float> py_vec;
  std::vector<float> pz_vec;
  std::vector<float> vx_vec;
  std::vector<float> vy_vec;
  std::vector<float> vz_vec;
  std::vector<int> charge_vec;
  std::vector<float> beta_vec;
  std::vector<float> chi2pid_vec;
  std::vector<int> status_vec;

  std::vector<int> cal_pindex_vec;
  std::vector<int> cal_detector_vec;
  std::vector<int> cal_sector_vec;
  std::vector<int> cal_layer_vec;
  std::vector<float> cal_energy_vec;
  std::vector<float> cal_time_vec;
  std::vector<float> cal_path_vec;
  std::vector<float> cal_x_vec;
  std::vector<float> cal_y_vec;
  std::vector<float> cal_z_vec;
  std::vector<float> cal_lu_vec;
  std::vector<float> cal_lv_vec;
  std::vector<float> cal_lw_vec;

  std::vector<int> chern_pindex_vec;
  std::vector<int> chern_detector_vec;
  std::vector<int> chern_sector_vec;
  std::vector<float> chern_nphe_vec;
  std::vector<float> chern_time_vec;
  std::vector<float> chern_path_vec;
  std::vector<float> chern_theta_vec;
  std::vector<float> chern_phi_vec;

  std::vector<int> fortag_pindex_vec;
  std::vector<int> fortag_detector_vec;
  std::vector<float> fortag_energy_vec;
  std::vector<float> fortag_time_vec;
  std::vector<float> fortag_path_vec;
  std::vector<float> fortag_x_vec;
  std::vector<float> fortag_y_vec;
  std::vector<float> fortag_z_vec;
  std::vector<float> fortag_dx_vec;
  std::vector<float> fortag_dy_vec;
  std::vector<float> fortag_radius_vec;
  std::vector<int> fortag_size_vec;

  std::vector<int> scint_pindex_vec;
  std::vector<int> scint_detector_vec;
  std::vector<int> scint_sector_vec;
  std::vector<int> scint_layer_vec;
  std::vector<int> scint_component_vec;
  std::vector<float> scint_energy_vec;
  std::vector<float> scint_time_vec;
  std::vector<float> scint_path_vec;

  std::vector<int> dc_sector_vec;
  std::vector<float> dc_px_vec;
  std::vector<float> dc_py_vec;
  std::vector<float> dc_pz_vec;
  std::vector<float> dc_vx_vec;
  std::vector<float> dc_vy_vec;
  std::vector<float> dc_vz_vec;

  std::vector<float> cvt_px_vec;
  std::vector<float> cvt_py_vec;
  std::vector<float> cvt_pz_vec;
  std::vector<float> cvt_vx_vec;
  std::vector<float> cvt_vy_vec;
  std::vector<float> cvt_vz_vec;

  std::vector<float> ec_tot_energy;
  std::vector<float> ec_pcal_energy;
  std::vector<int> ec_pcal_sec;
  std::vector<float> ec_pcal_time;
  std::vector<float> ec_pcal_path;
  std::vector<float> ec_pcal_x;
  std::vector<float> ec_pcal_y;
  std::vector<float> ec_pcal_z;
  std::vector<float> ec_pcal_lu;
  std::vector<float> ec_pcal_lv;
  std::vector<float> ec_pcal_lw;

  std::vector<float> ec_ecin_energy;
  std::vector<int> ec_ecin_sec;
  std::vector<float> ec_ecin_time;
  std::vector<float> ec_ecin_path;
  std::vector<float> ec_ecin_x;
  std::vector<float> ec_ecin_y;
  std::vector<float> ec_ecin_z;
  std::vector<float> ec_ecin_lu;
  std::vector<float> ec_ecin_lv;
  std::vector<float> ec_ecin_lw;

  std::vector<float> ec_ecout_energy;
  std::vector<int> ec_ecout_sec;
  std::vector<float> ec_ecout_time;
  std::vector<float> ec_ecout_path;
  std::vector<float> ec_ecout_x;
  std::vector<float> ec_ecout_y;
  std::vector<float> ec_ecout_z;
  std::vector<float> ec_ecout_lu;
  std::vector<float> ec_ecout_lv;
  std::vector<float> ec_ecout_lw;

  std::vector<float> cc_nphe_tot;
  std::vector<int> cc_ltcc_sec;
  std::vector<float> cc_ltcc_nphe;
  std::vector<float> cc_ltcc_time;
  std::vector<float> cc_ltcc_path;
  std::vector<float> cc_ltcc_theta;
  std::vector<float> cc_ltcc_phi;
  std::vector<int> cc_htcc_sec;
  std::vector<float> cc_htcc_nphe;
  std::vector<float> cc_htcc_time;
  std::vector<float> cc_htcc_path;
  std::vector<float> cc_htcc_theta;
  std::vector<float> cc_htcc_phi;

  std::vector<int> sc_ftof_sec;
  std::vector<float> sc_ftof_time;
  std::vector<float> sc_ftof_path;
  std::vector<float> sc_ftof_layer;
  std::vector<float> sc_ftof_energy;
  std::vector<float> sc_ftof_x;
  std::vector<float> sc_ftof_y;
  std::vector<float> sc_ftof_z;
  std::vector<float> sc_ftof_hx;
  std::vector<float> sc_ftof_hy;
  std::vector<float> sc_ftof_hz;

  std::vector<float> sc_ctof_time;
  std::vector<float> sc_ctof_path;
  std::vector<float> sc_ctof_energy;
  std::vector<float> sc_ctof_x;
  std::vector<float> sc_ctof_y;
  std::vector<float> sc_ctof_z;
  std::vector<float> sc_ctof_hx;
  std::vector<float> sc_ctof_hy;
  std::vector<float> sc_ctof_hz;

  std::vector<float> ft_cal_energy;
  std::vector<float> ft_cal_time;
  std::vector<float> ft_cal_path;
  std::vector<float> ft_cal_x;
  std::vector<float> ft_cal_y;
  std::vector<float> ft_cal_z;
  std::vector<float> ft_cal_dx;
  std::vector<float> ft_cal_dy;
  std::vector<float> ft_cal_radius;

  std::vector<float> ft_hodo_energy;
  std::vector<float> ft_hodo_time;
  std::vector<float> ft_hodo_path;
  std::vector<float> ft_hodo_x;
  std::vector<float> ft_hodo_y;
  std::vector<float> ft_hodo_z;
  std::vector<float> ft_hodo_dx;
  std::vector<float> ft_hodo_dy;
  std::vector<float> ft_hodo_radius;

  clas12->Branch("run", &run_vec);
  clas12->Branch("event", &event_vec);
  clas12->Branch("torus", &torus_vec);
  clas12->Branch("solenoid", &solenoid_vec);
  clas12->Branch("crate", &crate_vec);
  clas12->Branch("slot", &slot_vec);
  clas12->Branch("channel", &channel_vec);
  clas12->Branch("helicity", &helicity_vec);
  clas12->Branch("quartet", &quartet_vec);
  clas12->Branch("value", &value_vec);
  clas12->Branch("STTime", &STTime_vec);
  clas12->Branch("RFTime", &RFTime_vec);

  clas12->Branch("pid", &pid_vec);
  clas12->Branch("px", &px_vec);
  clas12->Branch("py", &py_vec);
  clas12->Branch("pz", &pz_vec);
  clas12->Branch("vx", &vx_vec);
  clas12->Branch("vy", &vy_vec);
  clas12->Branch("vz", &vz_vec);
  clas12->Branch("charge", &charge_vec);
  clas12->Branch("beta", &beta_vec);
  clas12->Branch("chi2pid", &chi2pid_vec);
  clas12->Branch("status", &status_vec);

  clas12->Branch("ec_tot_energy", &ec_tot_energy);
  clas12->Branch("ec_pcal_energy", &ec_pcal_energy);
  clas12->Branch("ec_pcal_sec", &ec_pcal_sec);
  clas12->Branch("ec_pcal_time", &ec_pcal_time);
  clas12->Branch("ec_pcal_path", &ec_pcal_path);
  clas12->Branch("ec_pcal_x", &ec_pcal_x);
  clas12->Branch("ec_pcal_y", &ec_pcal_y);
  clas12->Branch("ec_pcal_z", &ec_pcal_z);
  clas12->Branch("ec_pcal_lu", &ec_pcal_lu);
  clas12->Branch("ec_pcal_lv", &ec_pcal_lv);
  clas12->Branch("ec_pcal_lw", &ec_pcal_lw);

  clas12->Branch("ec_ecin_energy", &ec_ecin_energy);
  clas12->Branch("ec_ecin_sec", &ec_ecin_sec);
  clas12->Branch("ec_ecin_time", &ec_ecin_time);
  clas12->Branch("ec_ecin_path", &ec_ecin_path);
  clas12->Branch("ec_ecin_x", &ec_ecin_x);
  clas12->Branch("ec_ecin_y", &ec_ecin_y);
  clas12->Branch("ec_ecin_z", &ec_ecin_z);
  clas12->Branch("ec_ecin_lu", &ec_ecin_lu);
  clas12->Branch("ec_ecin_lv", &ec_ecin_lv);
  clas12->Branch("ec_ecin_lw", &ec_ecin_lw);

  clas12->Branch("ec_ecout_energy", &ec_ecout_energy);
  clas12->Branch("ec_ecout_sec", &ec_ecout_sec);
  clas12->Branch("ec_ecout_time", &ec_ecout_time);
  clas12->Branch("ec_ecout_path", &ec_ecout_path);
  clas12->Branch("ec_ecout_x", &ec_ecout_x);
  clas12->Branch("ec_ecout_y", &ec_ecout_y);
  clas12->Branch("ec_ecout_z", &ec_ecout_z);
  clas12->Branch("ec_ecout_lu", &ec_ecout_lu);
  clas12->Branch("ec_ecout_lv", &ec_ecout_lv);
  clas12->Branch("ec_ecout_lw", &ec_ecout_lw);

  clas12->Branch("dc_sector", &dc_sector_vec);
  clas12->Branch("dc_px", &dc_px_vec);
  clas12->Branch("dc_py", &dc_py_vec);
  clas12->Branch("dc_pz", &dc_pz_vec);
  clas12->Branch("dc_vx", &dc_vx_vec);
  clas12->Branch("dc_vy", &dc_vy_vec);
  clas12->Branch("dc_vz", &dc_vz_vec);

  clas12->Branch("cvt_px", &cvt_px_vec);
  clas12->Branch("cvt_py", &cvt_py_vec);
  clas12->Branch("cvt_pz", &cvt_pz_vec);
  clas12->Branch("cvt_vx", &cvt_vx_vec);
  clas12->Branch("cvt_vy", &cvt_vy_vec);
  clas12->Branch("cvt_vz", &cvt_vz_vec);

  clas12->Branch("cc_nphe_tot", &cc_nphe_tot);
  clas12->Branch("cc_ltcc_sec", &cc_ltcc_sec);
  clas12->Branch("cc_ltcc_nphe", &cc_ltcc_nphe);
  clas12->Branch("cc_ltcc_time", &cc_ltcc_time);
  clas12->Branch("cc_ltcc_path", &cc_ltcc_path);
  clas12->Branch("cc_ltcc_theta", &cc_ltcc_theta);
  clas12->Branch("cc_ltcc_phi", &cc_ltcc_phi);

  clas12->Branch("cc_htcc_sec", &cc_htcc_sec);
  clas12->Branch("cc_htcc_nphe", &cc_htcc_nphe);
  clas12->Branch("cc_htcc_time", &cc_htcc_time);
  clas12->Branch("cc_htcc_path", &cc_htcc_path);
  clas12->Branch("cc_htcc_theta", &cc_htcc_theta);
  clas12->Branch("cc_htcc_phi", &cc_htcc_phi);

  clas12->Branch("sc_ftof_sec", &sc_ftof_sec);
  clas12->Branch("sc_ftof_time", &sc_ftof_time);
  clas12->Branch("sc_ftof_path", &sc_ftof_path);
  clas12->Branch("sc_ftof_layer", &sc_ftof_layer);

  clas12->Branch("sc_ftof_energy", &sc_ftof_energy);
  clas12->Branch("sc_ctof_time", &sc_ctof_time);
  clas12->Branch("sc_ctof_path", &sc_ctof_path);
  clas12->Branch("sc_ctof_energy", &sc_ctof_energy);

  clas12->Branch("ft_cal_energy", &ft_cal_energy);
  clas12->Branch("ft_cal_time", &ft_cal_time);
  clas12->Branch("ft_cal_path", &ft_cal_path);
  clas12->Branch("ft_cal_x", &ft_cal_x);
  clas12->Branch("ft_cal_y", &ft_cal_y);
  clas12->Branch("ft_cal_z", &ft_cal_z);
  clas12->Branch("ft_cal_dx", &ft_cal_dx);
  clas12->Branch("ft_cal_dy", &ft_cal_dy);
  clas12->Branch("ft_cal_radius", &ft_cal_radius);

  clas12->Branch("ft_hodo_energy", &ft_hodo_energy);
  clas12->Branch("ft_hodo_time", &ft_hodo_time);
  clas12->Branch("ft_hodo_path", &ft_hodo_path);
  clas12->Branch("ft_hodo_x", &ft_hodo_x);
  clas12->Branch("ft_hodo_y", &ft_hodo_y);
  clas12->Branch("ft_hodo_z", &ft_hodo_z);
  clas12->Branch("ft_hodo_dx", &ft_hodo_dx);
  clas12->Branch("ft_hodo_dy", &ft_hodo_dy);
  clas12->Branch("ft_hodo_radius", &ft_hodo_radius);

  int entry = 0;
  int l = 0;
  int len_pid = 0;
  int len_pindex = 0;
  while (reader.next() == true) {
    entry++;
    if ((entry % 1000) == 0) std::cerr << "\t" << entry << "\r\r" << std::flush;

    if (pid_node->getLength() <= 0) continue;

    l = run_node->getLength();
    run_vec.resize(l);
    event_vec.resize(l);
    torus_vec.resize(l);
    solenoid_vec.resize(l);

    for (int i = 0; i < l; i++) {
      run_vec[i] = run_node->getValue(i);
      event_vec[i] = event_node->getValue(i);
      torus_vec[i] = torus_node->getValue(i);
      solenoid_vec[i] = solenoid_node->getValue(i);
    }

    l = crate_node->getLength();
    crate_vec.resize(l);
    slot_vec.resize(l);
    channel_vec.resize(l);
    helicity_vec.resize(l);
    quartet_vec.resize(l);
    value_vec.resize(l);

    for (int i = 0; i < l; i++) {
      crate_vec[i] = crate_node->getValue(i);
      slot_vec[i] = slot_node->getValue(i);
      channel_vec[i] = channel_node->getValue(i);
      helicity_vec[i] = helicity_node->getValue(i);
      quartet_vec[i] = quartet_node->getValue(i);
      value_vec[i] = value_node->getValue(i);
    }

    l = STTime_node->getLength();
    STTime_vec.resize(l);
    RFTime_vec.resize(l);

    for (int i = 0; i < l; i++) {
      STTime_vec[i] = STTime_node->getValue(i);
      RFTime_vec[i] = RFTime_node->getValue(i);
    }

    l = pid_node->getLength();
    pid_vec.resize(l);
    px_vec.resize(l);
    py_vec.resize(l);
    pz_vec.resize(l);
    vx_vec.resize(l);
    vy_vec.resize(l);
    vz_vec.resize(l);
    charge_vec.resize(l);
    beta_vec.resize(l);
    chi2pid_vec.resize(l);
    status_vec.resize(l);

    for (int i = 0; i < l; i++) {
      pid_vec[i] = pid_node->getValue(i);
      px_vec[i] = px_node->getValue(i);
      py_vec[i] = py_node->getValue(i);
      pz_vec[i] = pz_node->getValue(i);
      vx_vec[i] = vx_node->getValue(i);
      vy_vec[i] = vy_node->getValue(i);
      vz_vec[i] = vz_node->getValue(i);
      charge_vec[i] = charge_node->getValue(i);
      beta_vec[i] = ((beta_node->getValue(i) != -9999) ? beta_node->getValue(i) : NaN);
      chi2pid_vec[i] = chi2pid_node->getValue(i);
      status_vec[i] = status_node->getValue(i);
    }

    len_pid = pid_node->getLength();
    len_pindex = cal_pindex_node->getLength();

    ec_tot_energy.resize(len_pid);
    ec_pcal_energy.resize(len_pid);
    ec_pcal_sec.resize(len_pid);
    ec_pcal_time.resize(len_pid);
    ec_pcal_path.resize(len_pid);
    ec_pcal_x.resize(len_pid);
    ec_pcal_y.resize(len_pid);
    ec_pcal_z.resize(len_pid);
    ec_pcal_lu.resize(len_pid);
    ec_pcal_lv.resize(len_pid);
    ec_pcal_lw.resize(len_pid);
    ec_ecin_energy.resize(len_pid);
    ec_ecin_sec.resize(len_pid);
    ec_ecin_time.resize(len_pid);
    ec_ecin_path.resize(len_pid);
    ec_ecin_x.resize(len_pid);
    ec_ecin_y.resize(len_pid);
    ec_ecin_z.resize(len_pid);
    ec_ecin_lu.resize(len_pid);
    ec_ecin_lv.resize(len_pid);
    ec_ecin_lw.resize(len_pid);
    ec_ecout_energy.resize(len_pid);
    ec_ecout_sec.resize(len_pid);
    ec_ecout_time.resize(len_pid);
    ec_ecout_path.resize(len_pid);
    ec_ecout_x.resize(len_pid);
    ec_ecout_y.resize(len_pid);
    ec_ecout_z.resize(len_pid);
    ec_ecout_lu.resize(len_pid);
    ec_ecout_lv.resize(len_pid);
    ec_ecout_lw.resize(len_pid);

    for (int i = 0; i < len_pid; i++) {
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
    }

    float pcal = 0.0;
    float einner = 0.0;
    float eouter = 0.0;
    float etot = 0.0;

    for (int i = 0; i < len_pid; i++) {
      for (int k = 0; k < len_pindex; k++) {
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
    }

    len_pid = pid_node->getLength();
    len_pindex = chern_pindex_node->getLength();

    cc_nphe_tot.resize(len_pid);

    cc_ltcc_sec.resize(len_pid);
    cc_ltcc_nphe.resize(len_pid);
    cc_ltcc_time.resize(len_pid);
    cc_ltcc_path.resize(len_pid);
    cc_ltcc_theta.resize(len_pid);
    cc_ltcc_phi.resize(len_pid);

    cc_htcc_sec.resize(len_pid);
    cc_htcc_nphe.resize(len_pid);
    cc_htcc_time.resize(len_pid);
    cc_htcc_path.resize(len_pid);
    cc_htcc_theta.resize(len_pid);
    cc_htcc_phi.resize(len_pid);

    for (int i = 0; i < len_pid; i++) {
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
    }

    float nphe_tot = 0.0;

    for (int i = 0; i < len_pid; i++) {
      for (int k = 0; k < len_pindex; k++) {
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
    }

    len_pid = pid_node->getLength();
    len_pindex = scint_pindex_node->getLength();

    sc_ftof_sec.resize(len_pid);
    sc_ftof_time.resize(len_pid);
    sc_ftof_path.resize(len_pid);
    sc_ftof_layer.resize(len_pid);
    sc_ftof_energy.resize(len_pid);

    sc_ctof_time.resize(len_pid);
    sc_ctof_path.resize(len_pid);
    sc_ctof_energy.resize(len_pid);

    for (int i = 0; i < len_pid; i++) {
      sc_ftof_sec[i] = -1;
      sc_ftof_time[i] = NaN;
      sc_ftof_path[i] = NaN;
      sc_ftof_layer[i] = NaN;
      sc_ftof_energy[i] = NaN;

      sc_ctof_time[i] = NaN;
      sc_ctof_path[i] = NaN;
      sc_ctof_energy[i] = NaN;
    }

    for (int i = 0; i < len_pid; i++) {
      for (int k = 0; k < len_pindex; k++) {
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
    }

    len_pid = pid_node->getLength();
    len_pindex = track_pindex_node->getLength();

    dc_sector_vec.resize(len_pid);
    dc_px_vec.resize(len_pid);
    dc_py_vec.resize(len_pid);
    dc_pz_vec.resize(len_pid);
    dc_vx_vec.resize(len_pid);
    dc_vy_vec.resize(len_pid);
    dc_vz_vec.resize(len_pid);

    cvt_px_vec.resize(len_pid);
    cvt_py_vec.resize(len_pid);
    cvt_pz_vec.resize(len_pid);
    cvt_vx_vec.resize(len_pid);
    cvt_vy_vec.resize(len_pid);
    cvt_vz_vec.resize(len_pid);

    for (int i = 0; i < len_pid; i++) {
      dc_sector_vec[i] = -1;
      dc_px_vec[i] = NaN;
      dc_py_vec[i] = NaN;
      dc_pz_vec[i] = NaN;
      dc_vx_vec[i] = NaN;
      dc_vy_vec[i] = NaN;
      dc_vz_vec[i] = NaN;

      cvt_px_vec[i] = NaN;
      cvt_py_vec[i] = NaN;
      cvt_pz_vec[i] = NaN;
      cvt_vx_vec[i] = NaN;
      cvt_vy_vec[i] = NaN;
      cvt_vz_vec[i] = NaN;
    }

    for (int i = 0; i < len_pid; i++) {
      for (int k = 0; k < len_pindex; k++) {
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
          cvt_px_vec[i] = track_px_nomm_node->getValue(k);
          cvt_py_vec[i] = track_py_nomm_node->getValue(k);
          cvt_pz_vec[i] = track_pz_nomm_node->getValue(k);
          cvt_vx_vec[i] = track_vx_nomm_node->getValue(k);
          cvt_vy_vec[i] = track_vy_nomm_node->getValue(k);
          cvt_vz_vec[i] = track_vz_nomm_node->getValue(k);

        } else if (pindex == i && detector == 6) {
          _dc_sec = track_sector_node->getValue(k);
          _dc_px = track_px_nomm_node->getValue(k);
          _dc_py = track_py_nomm_node->getValue(k);
          _dc_pz = track_pz_nomm_node->getValue(k);
          _dc_vx = track_vx_nomm_node->getValue(k);
          _dc_vy = track_vy_nomm_node->getValue(k);
          _dc_vz = track_vz_nomm_node->getValue(k);
        }

        if (dc_sector_vec[i] == -1) dc_sector_vec[i] = _dc_sec;
        if (dc_px_vec[i] != dc_px_vec[i]) dc_px_vec[i] = _dc_px;
        if (dc_py_vec[i] != dc_py_vec[i]) dc_py_vec[i] = _dc_py;
        if (dc_pz_vec[i] != dc_pz_vec[i]) dc_pz_vec[i] = _dc_pz;
        if (dc_vx_vec[i] != dc_vx_vec[i]) dc_vx_vec[i] = _dc_vx;
        if (dc_vy_vec[i] != dc_vy_vec[i]) dc_vy_vec[i] = _dc_vy;
        if (dc_vz_vec[i] != dc_vz_vec[i]) dc_vz_vec[i] = _dc_vz;

        if (cvt_px_vec[i] != cvt_px_vec[i]) cvt_px_vec[i] = _cvt_px;
        if (cvt_py_vec[i] != cvt_py_vec[i]) cvt_py_vec[i] = _cvt_py;
        if (cvt_pz_vec[i] != cvt_pz_vec[i]) cvt_pz_vec[i] = _cvt_pz;
        if (cvt_vx_vec[i] != cvt_vx_vec[i]) cvt_vx_vec[i] = _cvt_vx;
        if (cvt_vy_vec[i] != cvt_vy_vec[i]) cvt_vy_vec[i] = _cvt_vy;
        if (cvt_vz_vec[i] != cvt_vz_vec[i]) cvt_vz_vec[i] = _cvt_vz;
      }
    }

    len_pid = pid_node->getLength();
    len_pindex = fortag_pindex_node->getLength();

    ft_cal_energy.resize(len_pid);
    ft_cal_time.resize(len_pid);
    ft_cal_path.resize(len_pid);
    ft_cal_x.resize(len_pid);
    ft_cal_y.resize(len_pid);
    ft_cal_z.resize(len_pid);
    ft_cal_dx.resize(len_pid);
    ft_cal_dy.resize(len_pid);
    ft_cal_radius.resize(len_pid);

    ft_hodo_energy.resize(len_pid);
    ft_hodo_time.resize(len_pid);
    ft_hodo_path.resize(len_pid);
    ft_hodo_x.resize(len_pid);
    ft_hodo_y.resize(len_pid);
    ft_hodo_z.resize(len_pid);
    ft_hodo_dx.resize(len_pid);
    ft_hodo_dy.resize(len_pid);
    ft_hodo_radius.resize(len_pid);

    for (int i = 0; i < len_pid; i++) {
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

    for (int i = 0; i < len_pid; i++) {
      for (int k = 0; k < len_pindex; k++) {
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
    run_vec.clear();
    event_vec.clear();
    torus_vec.clear();
    solenoid_vec.clear();
    crate_vec.clear();
    slot_vec.clear();
    channel_vec.clear();
    helicity_vec.clear();
    quartet_vec.clear();
    value_vec.clear();
    NRUN_vec.clear();
    NEVENT_vec.clear();
    EVNTime_vec.clear();
    TYPE_vec.clear();
    TRG_vec.clear();
    BCG_vec.clear();
    STTime_vec.clear();
    RFTime_vec.clear();
    Helic_vec.clear();

    pid_vec.clear();
    px_vec.clear();
    py_vec.clear();
    pz_vec.clear();
    vx_vec.clear();
    vy_vec.clear();
    vz_vec.clear();
    charge_vec.clear();
    beta_vec.clear();
    chi2pid_vec.clear();
    status_vec.clear();

    cal_pindex_vec.clear();
    cal_detector_vec.clear();
    cal_sector_vec.clear();
    cal_layer_vec.clear();
    cal_energy_vec.clear();
    cal_time_vec.clear();
    cal_path_vec.clear();
    cal_x_vec.clear();
    cal_y_vec.clear();
    cal_z_vec.clear();
    cal_lu_vec.clear();
    cal_lv_vec.clear();
    cal_lw_vec.clear();

    chern_pindex_vec.clear();
    chern_detector_vec.clear();
    chern_sector_vec.clear();
    chern_nphe_vec.clear();
    chern_time_vec.clear();
    chern_path_vec.clear();
    chern_theta_vec.clear();
    chern_phi_vec.clear();

    fortag_pindex_vec.clear();
    fortag_detector_vec.clear();
    fortag_energy_vec.clear();
    fortag_time_vec.clear();
    fortag_path_vec.clear();
    fortag_x_vec.clear();
    fortag_y_vec.clear();
    fortag_z_vec.clear();
    fortag_dx_vec.clear();
    fortag_dy_vec.clear();
    fortag_radius_vec.clear();
    fortag_size_vec.clear();

    ec_tot_energy.clear();
    ec_pcal_energy.clear();
    ec_pcal_sec.clear();
    ec_pcal_time.clear();
    ec_pcal_path.clear();
    ec_pcal_x.clear();
    ec_pcal_y.clear();
    ec_pcal_z.clear();
    ec_pcal_lu.clear();
    ec_pcal_lv.clear();
    ec_pcal_lw.clear();
    ec_ecin_energy.clear();
    ec_ecin_sec.clear();
    ec_ecin_time.clear();
    ec_ecin_path.clear();
    ec_ecin_x.clear();
    ec_ecin_y.clear();
    ec_ecin_z.clear();
    ec_ecin_lu.clear();
    ec_ecin_lv.clear();
    ec_ecin_lw.clear();
    ec_ecout_energy.clear();
    ec_ecin_sec.clear();
    ec_ecin_time.clear();
    ec_ecin_path.clear();
    ec_ecin_x.clear();
    ec_ecin_y.clear();
    ec_ecin_z.clear();
    ec_ecin_lu.clear();
    ec_ecin_lv.clear();
    ec_ecin_lw.clear();

    cc_nphe_tot.clear();
    cc_ltcc_sec.clear();
    cc_ltcc_nphe.clear();
    cc_ltcc_time.clear();
    cc_ltcc_path.clear();
    cc_ltcc_theta.clear();
    cc_ltcc_phi.clear();
    cc_htcc_sec.clear();
    cc_htcc_nphe.clear();
    cc_htcc_time.clear();
    cc_htcc_path.clear();
    cc_htcc_theta.clear();
    cc_htcc_phi.clear();

    sc_ftof_sec.clear();
    sc_ftof_time.clear();
    sc_ftof_path.clear();
    sc_ftof_layer.clear();
    sc_ftof_energy.clear();

    sc_ctof_time.clear();
    sc_ctof_path.clear();
    sc_ctof_energy.clear();

    ft_cal_energy.clear();
    ft_cal_time.clear();
    ft_cal_path.clear();
    ft_cal_x.clear();
    ft_cal_y.clear();
    ft_cal_z.clear();
    ft_cal_dx.clear();
    ft_cal_dy.clear();
    ft_cal_radius.clear();

    ft_hodo_energy.clear();
    ft_hodo_time.clear();
    ft_hodo_path.clear();
    ft_hodo_x.clear();
    ft_hodo_y.clear();
    ft_hodo_z.clear();
    ft_hodo_dx.clear();
    ft_hodo_dy.clear();
    ft_hodo_radius.clear();

    dc_sector_vec.clear();
    dc_px_vec.clear();
    dc_py_vec.clear();
    dc_pz_vec.clear();
    dc_vx_vec.clear();
    dc_vy_vec.clear();
    dc_vz_vec.clear();

    cvt_px_vec.clear();
    cvt_py_vec.clear();
    cvt_pz_vec.clear();
    cvt_vx_vec.clear();
    cvt_vy_vec.clear();
    cvt_vz_vec.clear();
  }

  OutputFile->cd();
  clas12->Write();
  OutputFile->Close();

  std::chrono::duration<double> elapsed_full = (std::chrono::high_resolution_clock::now() - start_full);
  std::cout << "Elapsed time: " << elapsed_full.count() << " s" << std::endl;
  std::cout << "Events/Sec: " << entry / elapsed_full.count() << " Hz" << std::endl;

  return 0;
}
