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

  hipo::node<int32_t> *RUN_config_run_node = reader.getBranch<int32_t>(11, 1);
  hipo::node<int32_t> *RUN_config_event_node = reader.getBranch<int32_t>(11, 2);
  hipo::node<float> *RUN_config_torus_node = reader.getBranch<float>(11, 8);
  hipo::node<float> *RUN_config_solenoid_node = reader.getBranch<float>(11, 9);
  hipo::node<int8_t> *RAW_scaler_crate_node = reader.getBranch<int8_t>(20013, 1);
  hipo::node<int8_t> *RAW_scaler_slot_node = reader.getBranch<int8_t>(20013, 2);
  hipo::node<int16_t> *RAW_scaler_channel_node = reader.getBranch<int16_t>(20013, 3);
  hipo::node<int8_t> *RAW_scaler_helicity_node = reader.getBranch<int8_t>(20013, 4);
  hipo::node<int8_t> *RAW_scaler_quartet_node = reader.getBranch<int8_t>(20013, 5);
  hipo::node<int32_t> *RAW_scaler_value_node = reader.getBranch<int32_t>(20013, 6);
  hipo::node<int32_t> *REC_Event_NRUN_node = reader.getBranch<int32_t>(330, 1);
  hipo::node<int32_t> *REC_Event_NEVENT_node = reader.getBranch<int32_t>(330, 2);
  hipo::node<float> *REC_Event_EVNTime_node = reader.getBranch<float>(330, 3);
  hipo::node<int8_t> *REC_Event_TYPE_node = reader.getBranch<int8_t>(330, 4);
  hipo::node<int64_t> *REC_Event_TRG_node = reader.getBranch<int64_t>(330, 7);
  hipo::node<float> *REC_Event_BCG_node = reader.getBranch<float>(330, 8);
  hipo::node<float> *REC_Event_STTime_node = reader.getBranch<float>(330, 10);
  hipo::node<float> *REC_Event_RFTime_node = reader.getBranch<float>(330, 11);
  hipo::node<int8_t> *REC_Event_Helic_node = reader.getBranch<int8_t>(330, 12);
  hipo::node<int32_t> *REC_Particle_pid_node = reader.getBranch<int32_t>(331, 1);
  hipo::node<float> *REC_Particle_px_node = reader.getBranch<float>(331, 2);
  hipo::node<float> *REC_Particle_py_node = reader.getBranch<float>(331, 3);
  hipo::node<float> *REC_Particle_pz_node = reader.getBranch<float>(331, 4);
  hipo::node<float> *REC_Particle_vx_node = reader.getBranch<float>(331, 5);
  hipo::node<float> *REC_Particle_vy_node = reader.getBranch<float>(331, 6);
  hipo::node<float> *REC_Particle_vz_node = reader.getBranch<float>(331, 7);
  hipo::node<int8_t> *REC_Particle_charge_node = reader.getBranch<int8_t>(331, 8);
  hipo::node<float> *REC_Particle_beta_node = reader.getBranch<float>(331, 9);
  hipo::node<float> *REC_Particle_chi2pid_node = reader.getBranch<float>(331, 10);
  hipo::node<int16_t> *REC_Particle_status_node = reader.getBranch<int16_t>(331, 11);
  hipo::node<int16_t> *REC_Calorimeter_pindex_node = reader.getBranch<int16_t>(332, 2);
  hipo::node<int8_t> *REC_Calorimeter_detector_node = reader.getBranch<int8_t>(332, 3);
  hipo::node<int8_t> *REC_Calorimeter_sector_node = reader.getBranch<int8_t>(332, 4);
  hipo::node<int8_t> *REC_Calorimeter_layer_node = reader.getBranch<int8_t>(332, 5);
  hipo::node<float> *REC_Calorimeter_energy_node = reader.getBranch<float>(332, 6);
  hipo::node<float> *REC_Calorimeter_time_node = reader.getBranch<float>(332, 7);
  hipo::node<float> *REC_Calorimeter_path_node = reader.getBranch<float>(332, 8);
  hipo::node<float> *REC_Calorimeter_x_node = reader.getBranch<float>(332, 10);
  hipo::node<float> *REC_Calorimeter_y_node = reader.getBranch<float>(332, 11);
  hipo::node<float> *REC_Calorimeter_z_node = reader.getBranch<float>(332, 12);
  hipo::node<float> *REC_Calorimeter_lu_node = reader.getBranch<float>(332, 16);
  hipo::node<float> *REC_Calorimeter_lv_node = reader.getBranch<float>(332, 17);
  hipo::node<float> *REC_Calorimeter_lw_node = reader.getBranch<float>(332, 18);
  hipo::node<int16_t> *REC_Cherenkov_pindex_node = reader.getBranch<int16_t>(333, 2);
  hipo::node<int8_t> *REC_Cherenkov_detector_node = reader.getBranch<int8_t>(333, 3);
  hipo::node<int8_t> *REC_Cherenkov_sector_node = reader.getBranch<int8_t>(333, 4);
  hipo::node<float> *REC_Cherenkov_nphe_node = reader.getBranch<float>(333, 5);
  hipo::node<float> *REC_Cherenkov_time_node = reader.getBranch<float>(333, 6);
  hipo::node<float> *REC_Cherenkov_path_node = reader.getBranch<float>(333, 7);
  hipo::node<float> *REC_Cherenkov_theta_node = reader.getBranch<float>(333, 12);
  hipo::node<float> *REC_Cherenkov_phi_node = reader.getBranch<float>(333, 13);
  hipo::node<int16_t> *REC_ForwardTagger_pindex_node = reader.getBranch<int16_t>(334, 2);
  hipo::node<int8_t> *REC_ForwardTagger_detector_node = reader.getBranch<int8_t>(334, 3);
  hipo::node<float> *REC_ForwardTagger_energy_node = reader.getBranch<float>(334, 4);
  hipo::node<float> *REC_ForwardTagger_time_node = reader.getBranch<float>(334, 5);
  hipo::node<float> *REC_ForwardTagger_path_node = reader.getBranch<float>(334, 6);
  hipo::node<float> *REC_ForwardTagger_x_node = reader.getBranch<float>(334, 8);
  hipo::node<float> *REC_ForwardTagger_y_node = reader.getBranch<float>(334, 9);
  hipo::node<float> *REC_ForwardTagger_z_node = reader.getBranch<float>(334, 10);
  hipo::node<float> *REC_ForwardTagger_dx_node = reader.getBranch<float>(334, 11);
  hipo::node<float> *REC_ForwardTagger_dy_node = reader.getBranch<float>(334, 12);
  hipo::node<float> *REC_ForwardTagger_radius_node = reader.getBranch<float>(334, 13);
  hipo::node<int16_t> *REC_ForwardTagger_size_node = reader.getBranch<int16_t>(334, 14);
  hipo::node<int16_t> *REC_Scintillator_pindex_node = reader.getBranch<int16_t>(335, 2);
  hipo::node<int8_t> *REC_Scintillator_detector_node = reader.getBranch<int8_t>(335, 3);
  hipo::node<int8_t> *REC_Scintillator_sector_node = reader.getBranch<int8_t>(335, 4);
  hipo::node<int8_t> *REC_Scintillator_layer_node = reader.getBranch<int8_t>(335, 5);
  hipo::node<int16_t> *REC_Scintillator_component_node = reader.getBranch<int16_t>(335, 6);
  hipo::node<float> *REC_Scintillator_energy_node = reader.getBranch<float>(335, 7);
  hipo::node<float> *REC_Scintillator_time_node = reader.getBranch<float>(335, 8);
  hipo::node<float> *REC_Scintillator_path_node = reader.getBranch<float>(335, 9);
  hipo::node<int16_t> *REC_Track_pindex_node = reader.getBranch<int16_t>(336, 2);
  hipo::node<int8_t> *REC_Track_detector_node = reader.getBranch<int8_t>(336, 3);
  hipo::node<int8_t> *REC_Track_sector_node = reader.getBranch<int8_t>(336, 4);
  hipo::node<float> *REC_Track_chi2_node = reader.getBranch<float>(336, 7);
  hipo::node<int16_t> *REC_Track_NDF_node = reader.getBranch<int16_t>(336, 8);
  hipo::node<float> *REC_Track_chi2_nomm_node = reader.getBranch<float>(336, 15);
  hipo::node<int16_t> *REC_Track_NDF_nomm_node = reader.getBranch<int16_t>(336, 16);
  hipo::node<int16_t> *REC_Traj_pindex_node = reader.getBranch<int16_t>(340, 1);
  hipo::node<int16_t> *REC_Traj_detId_node = reader.getBranch<int16_t>(340, 3);
  hipo::node<float> *REC_Traj_x_node = reader.getBranch<float>(340, 5);
  hipo::node<float> *REC_Traj_y_node = reader.getBranch<float>(340, 6);
  hipo::node<float> *REC_Traj_z_node = reader.getBranch<float>(340, 7);
  hipo::node<float> *REC_Traj_cx_node = reader.getBranch<float>(340, 8);
  hipo::node<float> *REC_Traj_cy_node = reader.getBranch<float>(340, 9);
  hipo::node<float> *REC_Traj_cz_node = reader.getBranch<float>(340, 10);

  std::vector<int> RUN_config_run_vec;
  std::vector<int> RUN_config_event_vec;
  std::vector<float> RUN_config_torus_vec;
  std::vector<float> RUN_config_solenoid_vec;
  std::vector<int> RAW_scaler_crate_vec;
  std::vector<int> RAW_scaler_slot_vec;
  std::vector<int> RAW_scaler_channel_vec;
  std::vector<int> RAW_scaler_helicity_vec;
  std::vector<int> RAW_scaler_quartet_vec;
  std::vector<int> RAW_scaler_value_vec;
  std::vector<int> REC_Event_NRUN_vec;
  std::vector<int> REC_Event_NEVENT_vec;
  std::vector<float> REC_Event_EVNTime_vec;
  std::vector<int> REC_Event_TYPE_vec;
  std::vector<int> REC_Event_TRG_vec;
  std::vector<float> REC_Event_BCG_vec;
  std::vector<float> REC_Event_STTime_vec;
  std::vector<float> REC_Event_RFTime_vec;
  std::vector<int> REC_Event_Helic_vec;
  std::vector<int> REC_Particle_pid_vec;
  std::vector<float> REC_Particle_px_vec;
  std::vector<float> REC_Particle_py_vec;
  std::vector<float> REC_Particle_pz_vec;
  std::vector<float> REC_Particle_vx_vec;
  std::vector<float> REC_Particle_vy_vec;
  std::vector<float> REC_Particle_vz_vec;
  std::vector<int> REC_Particle_charge_vec;
  std::vector<float> REC_Particle_beta_vec;
  std::vector<float> REC_Particle_chi2pid_vec;
  std::vector<int> REC_Particle_status_vec;
  std::vector<int> REC_Calorimeter_pindex_vec;
  std::vector<int> REC_Calorimeter_detector_vec;
  std::vector<int> REC_Calorimeter_sector_vec;
  std::vector<int> REC_Calorimeter_layer_vec;
  std::vector<float> REC_Calorimeter_energy_vec;
  std::vector<float> REC_Calorimeter_time_vec;
  std::vector<float> REC_Calorimeter_path_vec;
  std::vector<float> REC_Calorimeter_x_vec;
  std::vector<float> REC_Calorimeter_y_vec;
  std::vector<float> REC_Calorimeter_z_vec;
  std::vector<float> REC_Calorimeter_lu_vec;
  std::vector<float> REC_Calorimeter_lv_vec;
  std::vector<float> REC_Calorimeter_lw_vec;
  std::vector<int> REC_Cherenkov_pindex_vec;
  std::vector<int> REC_Cherenkov_detector_vec;
  std::vector<int> REC_Cherenkov_sector_vec;
  std::vector<float> REC_Cherenkov_nphe_vec;
  std::vector<float> REC_Cherenkov_time_vec;
  std::vector<float> REC_Cherenkov_path_vec;
  std::vector<float> REC_Cherenkov_theta_vec;
  std::vector<float> REC_Cherenkov_phi_vec;
  std::vector<int> REC_ForwardTagger_pindex_vec;
  std::vector<int> REC_ForwardTagger_detector_vec;
  std::vector<float> REC_ForwardTagger_energy_vec;
  std::vector<float> REC_ForwardTagger_time_vec;
  std::vector<float> REC_ForwardTagger_path_vec;
  std::vector<float> REC_ForwardTagger_x_vec;
  std::vector<float> REC_ForwardTagger_y_vec;
  std::vector<float> REC_ForwardTagger_z_vec;
  std::vector<float> REC_ForwardTagger_dx_vec;
  std::vector<float> REC_ForwardTagger_dy_vec;
  std::vector<float> REC_ForwardTagger_radius_vec;
  std::vector<int> REC_ForwardTagger_size_vec;
  std::vector<int> REC_Scintillator_pindex_vec;
  std::vector<int> REC_Scintillator_detector_vec;
  std::vector<int> REC_Scintillator_sector_vec;
  std::vector<int> REC_Scintillator_layer_vec;
  std::vector<int> REC_Scintillator_component_vec;
  std::vector<float> REC_Scintillator_energy_vec;
  std::vector<float> REC_Scintillator_time_vec;
  std::vector<float> REC_Scintillator_path_vec;
  std::vector<int> REC_Track_pindex_vec;
  std::vector<int> REC_Track_detector_vec;
  std::vector<int> REC_Track_sector_vec;
  std::vector<float> REC_Track_chi2_vec;
  std::vector<int> REC_Track_NDF_vec;
  std::vector<float> REC_Track_chi2_nomm_vec;
  std::vector<int> REC_Track_NDF_nomm_vec;
  std::vector<int> REC_Traj_pindex_vec;
  std::vector<int> REC_Traj_detId_vec;
  std::vector<float> REC_Traj_x_vec;
  std::vector<float> REC_Traj_y_vec;
  std::vector<float> REC_Traj_z_vec;
  std::vector<float> REC_Traj_cx_vec;
  std::vector<float> REC_Traj_cy_vec;
  std::vector<float> REC_Traj_cz_vec;

  std::vector<int> ec_sec;
  std::vector<float> ec_pcal;
  std::vector<float> ec_ecin;
  std::vector<float> ec_ecout;
  std::vector<float> ec_etot;
  std::vector<float> ec_time;
  std::vector<float> ec_path;
  std::vector<float> ec_x;
  std::vector<float> ec_y;
  std::vector<float> ec_z;
  std::vector<float> ec_lu;
  std::vector<float> ec_lv;
  std::vector<float> ec_lw;

  std::vector<int> cc_sec;
  std::vector<float> cc_nphe_ltcc;
  std::vector<float> cc_nphe_htcc;
  std::vector<float> cc_nphe_tot;
  std::vector<float> cc_time;
  std::vector<float> cc_path;
  std::vector<float> cc_theta;
  std::vector<float> cc_phi;

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

  clas12->Branch("run", &RUN_config_run_vec);
  clas12->Branch("event", &RUN_config_event_vec);
  clas12->Branch("torus", &RUN_config_torus_vec);
  clas12->Branch("solenoid", &RUN_config_solenoid_vec);
  clas12->Branch("crate", &RAW_scaler_crate_vec);
  clas12->Branch("slot", &RAW_scaler_slot_vec);
  clas12->Branch("channel", &RAW_scaler_channel_vec);
  clas12->Branch("helicity", &RAW_scaler_helicity_vec);
  clas12->Branch("quartet", &RAW_scaler_quartet_vec);
  clas12->Branch("value", &RAW_scaler_value_vec);
  clas12->Branch("STTime", &REC_Event_STTime_vec);
  clas12->Branch("RFTime", &REC_Event_RFTime_vec);
  clas12->Branch("pid", &REC_Particle_pid_vec);
  clas12->Branch("px", &REC_Particle_px_vec);
  clas12->Branch("py", &REC_Particle_py_vec);
  clas12->Branch("pz", &REC_Particle_pz_vec);
  clas12->Branch("vx", &REC_Particle_vx_vec);
  clas12->Branch("vy", &REC_Particle_vy_vec);
  clas12->Branch("vz", &REC_Particle_vz_vec);
  clas12->Branch("charge", &REC_Particle_charge_vec);
  clas12->Branch("beta", &REC_Particle_beta_vec);
  clas12->Branch("chi2pid", &REC_Particle_chi2pid_vec);
  clas12->Branch("status", &REC_Particle_status_vec);
  /*
    clas12->Branch("REC_Calorimeter_pindex", &REC_Calorimeter_pindex_vec);
    clas12->Branch("REC_Calorimeter_detector", &REC_Calorimeter_detector_vec);
    clas12->Branch("REC_Calorimeter_sector", &REC_Calorimeter_sector_vec);
    clas12->Branch("REC_Calorimeter_layer", &REC_Calorimeter_layer_vec);
    clas12->Branch("REC_Calorimeter_energy", &REC_Calorimeter_energy_vec);
    clas12->Branch("REC_Calorimeter_time", &REC_Calorimeter_time_vec);
    clas12->Branch("REC_Calorimeter_path", &REC_Calorimeter_path_vec);
    clas12->Branch("REC_Calorimeter_x", &REC_Calorimeter_x_vec);
    clas12->Branch("REC_Calorimeter_y", &REC_Calorimeter_y_vec);
    clas12->Branch("REC_Calorimeter_z", &REC_Calorimeter_z_vec);
    clas12->Branch("REC_Calorimeter_lu", &REC_Calorimeter_lu_vec);
    clas12->Branch("REC_Calorimeter_lv", &REC_Calorimeter_lv_vec);
    clas12->Branch("REC_Calorimeter_lw", &REC_Calorimeter_lw_vec);
    clas12->Branch("REC_Cherenkov_pindex", &REC_Cherenkov_pindex_vec);
    clas12->Branch("REC_Cherenkov_detector", &REC_Cherenkov_detector_vec);
    clas12->Branch("REC_Cherenkov_sector", &REC_Cherenkov_sector_vec);
    clas12->Branch("REC_Cherenkov_nphe", &REC_Cherenkov_nphe_vec);
    clas12->Branch("REC_Cherenkov_time", &REC_Cherenkov_time_vec);
    clas12->Branch("REC_Cherenkov_path", &REC_Cherenkov_path_vec);
    clas12->Branch("REC_Cherenkov_theta", &REC_Cherenkov_theta_vec);
    clas12->Branch("REC_Cherenkov_phi", &REC_Cherenkov_phi_vec);
  */
  clas12->Branch("REC_ForwardTagger_pindex", &REC_ForwardTagger_pindex_vec);
  clas12->Branch("REC_ForwardTagger_detector", &REC_ForwardTagger_detector_vec);
  clas12->Branch("REC_ForwardTagger_energy", &REC_ForwardTagger_energy_vec);
  clas12->Branch("REC_ForwardTagger_time", &REC_ForwardTagger_time_vec);
  clas12->Branch("REC_ForwardTagger_path", &REC_ForwardTagger_path_vec);
  clas12->Branch("REC_ForwardTagger_x", &REC_ForwardTagger_x_vec);
  clas12->Branch("REC_ForwardTagger_y", &REC_ForwardTagger_y_vec);
  clas12->Branch("REC_ForwardTagger_z", &REC_ForwardTagger_z_vec);
  clas12->Branch("REC_ForwardTagger_dx", &REC_ForwardTagger_dx_vec);
  clas12->Branch("REC_ForwardTagger_dy", &REC_ForwardTagger_dy_vec);
  clas12->Branch("REC_ForwardTagger_radius", &REC_ForwardTagger_radius_vec);
  clas12->Branch("REC_ForwardTagger_size", &REC_ForwardTagger_size_vec);
  /*
    clas12->Branch("REC_Scintillator_pindex", &REC_Scintillator_pindex_vec);
    clas12->Branch("REC_Scintillator_detector", &REC_Scintillator_detector_vec);
    clas12->Branch("REC_Scintillator_sector", &REC_Scintillator_sector_vec);
    clas12->Branch("REC_Scintillator_layer", &REC_Scintillator_layer_vec);
    clas12->Branch("REC_Scintillator_component", &REC_Scintillator_component_vec);
    clas12->Branch("REC_Scintillator_energy", &REC_Scintillator_energy_vec);
    clas12->Branch("REC_Scintillator_time", &REC_Scintillator_time_vec);
    clas12->Branch("REC_Scintillator_path", &REC_Scintillator_path_vec);
  */
  clas12->Branch("REC_Track_pindex", &REC_Track_pindex_vec);
  clas12->Branch("REC_Track_detector", &REC_Track_detector_vec);
  clas12->Branch("REC_Track_sector", &REC_Track_sector_vec);
  clas12->Branch("REC_Track_chi2", &REC_Track_chi2_vec);
  clas12->Branch("REC_Track_NDF", &REC_Track_NDF_vec);
  clas12->Branch("REC_Track_chi2_nomm", &REC_Track_chi2_nomm_vec);
  clas12->Branch("REC_Track_NDF_nomm", &REC_Track_NDF_nomm_vec);
  clas12->Branch("REC_Traj_pindex", &REC_Traj_pindex_vec);
  clas12->Branch("REC_Traj_detId", &REC_Traj_detId_vec);
  clas12->Branch("REC_Traj_x", &REC_Traj_x_vec);
  clas12->Branch("REC_Traj_y", &REC_Traj_y_vec);
  clas12->Branch("REC_Traj_z", &REC_Traj_z_vec);
  clas12->Branch("REC_Traj_cx", &REC_Traj_cx_vec);
  clas12->Branch("REC_Traj_cy", &REC_Traj_cy_vec);
  clas12->Branch("REC_Traj_cz", &REC_Traj_cz_vec);

  clas12->Branch("ec_pcal", &ec_pcal);
  clas12->Branch("ec_ecin", &ec_ecin);
  clas12->Branch("ec_ecout", &ec_ecout);
  clas12->Branch("ec_etot", &ec_etot);
  clas12->Branch("ec_sec", &ec_sec);
  clas12->Branch("ec_time", &ec_time);
  clas12->Branch("ec_path", &ec_path);
  clas12->Branch("ec_x", &ec_x);
  clas12->Branch("ec_y", &ec_y);
  clas12->Branch("ec_z", &ec_z);
  clas12->Branch("ec_lu", &ec_lu);
  clas12->Branch("ec_lv", &ec_lv);
  clas12->Branch("ec_lw", &ec_lw);
  clas12->Branch("cc_sec", &cc_sec);
  clas12->Branch("cc_nphe_ltcc", &cc_nphe_ltcc);
  clas12->Branch("cc_nphe_htcc", &cc_nphe_htcc);
  clas12->Branch("cc_nphe_tot", &cc_nphe_tot);
  clas12->Branch("cc_time", &cc_time);
  clas12->Branch("cc_path", &cc_path);
  clas12->Branch("cc_theta", &cc_theta);
  clas12->Branch("cc_phi", &cc_phi);
  clas12->Branch("sc_ftof_sec", &sc_ftof_sec);
  clas12->Branch("sc_ftof_time", &sc_ftof_time);
  clas12->Branch("sc_ftof_path", &sc_ftof_path);
  clas12->Branch("sc_ftof_layer", &sc_ftof_layer);
  clas12->Branch("sc_ftof_energy", &sc_ftof_energy);
  clas12->Branch("sc_ctof_time", &sc_ctof_time);
  clas12->Branch("sc_ctof_path", &sc_ctof_path);
  clas12->Branch("sc_ctof_energy", &sc_ctof_energy);

  int entry = 0;
  int l = 0;
  int len_pid = 0;
  int len_pindex = 0;
  while (reader.next() == true) {
    entry++;
    if ((entry % 1000) == 0) std::cerr << "\t" << entry << "\r\r" << std::flush;
    if (REC_Particle_pid_node->getLength() <= 0) continue;

    l = RUN_config_run_node->getLength();
    RUN_config_run_vec.resize(l);
    for (int i = 0; i < l; i++) RUN_config_run_vec.at(i) = RUN_config_run_node->getValue(i);

    l = RUN_config_event_node->getLength();
    RUN_config_event_vec.resize(l);
    for (int i = 0; i < l; i++) RUN_config_event_vec.at(i) = RUN_config_event_node->getValue(i);

    l = RUN_config_torus_node->getLength();
    RUN_config_torus_vec.resize(l);
    for (int i = 0; i < l; i++) RUN_config_torus_vec.at(i) = RUN_config_torus_node->getValue(i);

    l = RUN_config_solenoid_node->getLength();
    RUN_config_solenoid_vec.resize(l);
    for (int i = 0; i < l; i++) RUN_config_solenoid_vec.at(i) = RUN_config_solenoid_node->getValue(i);

    l = RAW_scaler_crate_node->getLength();
    RAW_scaler_crate_vec.resize(l);
    for (int i = 0; i < l; i++) RAW_scaler_crate_vec.at(i) = RAW_scaler_crate_node->getValue(i);

    l = RAW_scaler_slot_node->getLength();
    RAW_scaler_slot_vec.resize(l);
    for (int i = 0; i < l; i++) RAW_scaler_slot_vec.at(i) = RAW_scaler_slot_node->getValue(i);

    l = RAW_scaler_channel_node->getLength();
    RAW_scaler_channel_vec.resize(l);
    for (int i = 0; i < l; i++) RAW_scaler_channel_vec.at(i) = RAW_scaler_channel_node->getValue(i);

    l = RAW_scaler_helicity_node->getLength();
    RAW_scaler_helicity_vec.resize(l);
    for (int i = 0; i < l; i++) RAW_scaler_helicity_vec.at(i) = RAW_scaler_helicity_node->getValue(i);

    l = RAW_scaler_quartet_node->getLength();
    RAW_scaler_quartet_vec.resize(l);
    for (int i = 0; i < l; i++) RAW_scaler_quartet_vec.at(i) = RAW_scaler_quartet_node->getValue(i);

    l = RAW_scaler_value_node->getLength();
    RAW_scaler_value_vec.resize(l);
    for (int i = 0; i < l; i++) RAW_scaler_value_vec.at(i) = RAW_scaler_value_node->getValue(i);

    l = REC_Event_STTime_node->getLength();
    REC_Event_STTime_vec.resize(l);
    for (int i = 0; i < l; i++) REC_Event_STTime_vec.at(i) = REC_Event_STTime_node->getValue(i);

    l = REC_Event_RFTime_node->getLength();
    REC_Event_RFTime_vec.resize(l);
    for (int i = 0; i < l; i++) REC_Event_RFTime_vec.at(i) = REC_Event_RFTime_node->getValue(i);

    l = REC_Particle_pid_node->getLength();
    REC_Particle_pid_vec.resize(l);
    for (int i = 0; i < l; i++) REC_Particle_pid_vec.at(i) = REC_Particle_pid_node->getValue(i);

    l = REC_Particle_px_node->getLength();
    REC_Particle_px_vec.resize(l);
    for (int i = 0; i < l; i++) REC_Particle_px_vec.at(i) = REC_Particle_px_node->getValue(i);

    l = REC_Particle_py_node->getLength();
    REC_Particle_py_vec.resize(l);
    for (int i = 0; i < l; i++) REC_Particle_py_vec.at(i) = REC_Particle_py_node->getValue(i);

    l = REC_Particle_pz_node->getLength();
    REC_Particle_pz_vec.resize(l);
    for (int i = 0; i < l; i++) REC_Particle_pz_vec.at(i) = REC_Particle_pz_node->getValue(i);

    l = REC_Particle_vx_node->getLength();
    REC_Particle_vx_vec.resize(l);
    for (int i = 0; i < l; i++) REC_Particle_vx_vec.at(i) = REC_Particle_vx_node->getValue(i);

    l = REC_Particle_vy_node->getLength();
    REC_Particle_vy_vec.resize(l);
    for (int i = 0; i < l; i++) REC_Particle_vy_vec.at(i) = REC_Particle_vy_node->getValue(i);

    l = REC_Particle_vz_node->getLength();
    REC_Particle_vz_vec.resize(l);
    for (int i = 0; i < l; i++) REC_Particle_vz_vec.at(i) = REC_Particle_vz_node->getValue(i);

    l = REC_Particle_charge_node->getLength();
    REC_Particle_charge_vec.resize(l);
    for (int i = 0; i < l; i++) REC_Particle_charge_vec.at(i) = REC_Particle_charge_node->getValue(i);

    l = REC_Particle_beta_node->getLength();
    REC_Particle_beta_vec.resize(l);
    for (int i = 0; i < l; i++)
      REC_Particle_beta_vec.at(i) =
          ((REC_Particle_beta_node->getValue(i) != -9999) ? REC_Particle_beta_node->getValue(i) : NaN);

    l = REC_Particle_chi2pid_node->getLength();
    REC_Particle_chi2pid_vec.resize(l);
    for (int i = 0; i < l; i++) REC_Particle_chi2pid_vec.at(i) = REC_Particle_chi2pid_node->getValue(i);

    l = REC_Particle_status_node->getLength();
    REC_Particle_status_vec.resize(l);
    for (int i = 0; i < l; i++) REC_Particle_status_vec.at(i) = REC_Particle_status_node->getValue(i);

    len_pid = REC_Particle_pid_node->getLength();
    len_pindex = REC_Calorimeter_pindex_node->getLength();
    ec_pcal.resize(len_pid);
    ec_ecin.resize(len_pid);
    ec_ecout.resize(len_pid);
    ec_etot.resize(len_pid);
    ec_sec.resize(len_pid);
    ec_time.resize(len_pid);
    ec_path.resize(len_pid);
    ec_x.resize(len_pid);
    ec_y.resize(len_pid);
    ec_z.resize(len_pid);
    ec_lu.resize(len_pid);
    ec_lv.resize(len_pid);
    ec_lw.resize(len_pid);

    for (int i = 0; i < len_pid; i++) {
      ec_sec[i] = -1;
      ec_pcal[i] = NaN;
      ec_ecin[i] = NaN;
      ec_ecout[i] = NaN;
      ec_etot[i] = NaN;
      ec_time[i] = NaN;
      ec_path[i] = NaN;
      ec_x[i] = NaN;
      ec_y[i] = NaN;
      ec_z[i] = NaN;
      ec_lu[i] = NaN;
      ec_lv[i] = NaN;
      ec_lw[i] = NaN;
    }

    float pcal = 0.0;
    float einner = 0.0;
    float eouter = 0.0;
    float etot = 0.0;

    for (int i = 0; i < len_pid; i++) {
      for (int k = 0; k < len_pindex; k++) {
        int pindex = REC_Calorimeter_pindex_node->getValue(k);
        int detector = REC_Calorimeter_detector_node->getValue(k);
        int sec = -1;
        float t = NaN;
        float r = NaN;
        float x = NaN;
        float y = NaN;
        float z = NaN;
        float lu = NaN;
        float lv = NaN;
        float lw = NaN;
        if (pindex == i && detector == 7) {
          int layer = REC_Calorimeter_layer_node->getValue(k);
          float energy = REC_Calorimeter_energy_node->getValue(k);
          t = REC_Calorimeter_time_node->getValue(k);
          r = REC_Calorimeter_path_node->getValue(k);
          x = REC_Calorimeter_x_node->getValue(k);
          y = REC_Calorimeter_y_node->getValue(k);
          z = REC_Calorimeter_z_node->getValue(k);
          lu = REC_Calorimeter_lu_node->getValue(k);
          lv = REC_Calorimeter_lv_node->getValue(k);
          lw = REC_Calorimeter_lw_node->getValue(k);
          sec = REC_Calorimeter_sector_node->getValue(k);

          etot += energy;
          if (layer == 1)
            pcal += energy;
          else if (layer == 4)
            einner += energy;
          else if (layer == 7)
            eouter += energy;
        }
        if (ec_time[i] != ec_time[i]) ec_time[i] = t;
        if (ec_path[i] != ec_path[i]) ec_path[i] = r;
        if (ec_x[i] != ec_x[i]) ec_x[i] = x;
        if (ec_y[i] != ec_y[i]) ec_y[i] = y;
        if (ec_z[i] != ec_z[i]) ec_z[i] = z;
        if (ec_lu[i] != ec_lu[i]) ec_lu[i] = lu;
        if (ec_lv[i] != ec_lv[i]) ec_lv[i] = lv;
        if (ec_lw[i] != ec_lw[i]) ec_lw[i] = lw;
        if (ec_sec[i] == -1) ec_sec[i] = sec;
      }
      if (ec_pcal[i] != ec_pcal[i]) ec_pcal[i] = ((pcal != 0.0) ? pcal : NaN);
      if (ec_ecin[i] != ec_ecin[i]) ec_ecin[i] = ((einner != 0.0) ? einner : NaN);
      if (ec_ecout[i] != ec_ecout[i]) ec_ecout[i] = ((eouter != 0.0) ? eouter : NaN);
      if (ec_etot[i] != ec_etot[i]) ec_etot[i] = ((etot != 0.0) ? etot : NaN);
    }

    len_pid = REC_Particle_pid_node->getLength();
    len_pindex = REC_Cherenkov_pindex_node->getLength();
    cc_sec.resize(len_pid);
    cc_nphe_ltcc.resize(len_pid);
    cc_nphe_htcc.resize(len_pid);
    cc_nphe_tot.resize(len_pid);
    cc_time.resize(len_pid);
    cc_path.resize(len_pid);
    cc_theta.resize(len_pid);
    cc_phi.resize(len_pid);

    for (int i = 0; i < len_pid; i++) {
      cc_sec[i] = -1;
      cc_nphe_ltcc[i] = NaN;
      cc_nphe_htcc[i] = NaN;
      cc_nphe_tot[i] = NaN;
      cc_time[i] = NaN;
      cc_path[i] = NaN;
      cc_theta[i] = NaN;
      cc_phi[i] = NaN;
    }

    float nphe_ltcc = 0.0;
    float nphe_htcc = 0.0;
    float nphe_tot = 0.0;

    for (int i = 0; i < len_pid; i++) {
      for (int k = 0; k < len_pindex; k++) {
        int pindex = REC_Cherenkov_pindex_node->getValue(k);
        int detector = REC_Cherenkov_detector_node->getValue(k);

        int sec = -1;
        float t = NaN;
        float r = NaN;
        float theta = NaN;
        float phi = NaN;
        float nphe = NaN;

        if (pindex == i && (detector == 15 || detector == 16)) {
          sec = REC_Cherenkov_sector_node->getValue(k);
          t = REC_Cherenkov_time_node->getValue(k);
          r = REC_Cherenkov_path_node->getValue(k);
          theta = REC_Cherenkov_theta_node->getValue(k);
          phi = REC_Cherenkov_phi_node->getValue(k);
          nphe = REC_Cherenkov_nphe_node->getValue(k);
          nphe_tot += nphe;
          if (detector == 15)
            nphe_htcc += nphe;
          else if (detector == 16)
            nphe_ltcc += nphe;
        }
        if (cc_time[i] != cc_time[i]) cc_time[i] = t;
        if (cc_path[i] != cc_path[i]) cc_path[i] = r;
        if (cc_theta[i] != cc_theta[i]) cc_theta[i] = theta;
        if (cc_phi[i] != cc_phi[i]) cc_phi[i] = phi;
        if (cc_sec[i] == -1) cc_sec[i] = sec;
      }
      if (cc_nphe_ltcc[i] != cc_nphe_ltcc[i]) cc_nphe_ltcc[i] = ((nphe_ltcc != 0.0) ? nphe_ltcc : NaN);
      if (cc_nphe_htcc[i] != cc_nphe_htcc[i]) cc_nphe_htcc[i] = ((nphe_htcc != 0.0) ? nphe_htcc : NaN);
      if (cc_nphe_tot[i] != cc_nphe_tot[i]) cc_nphe_tot[i] = ((nphe_tot != 0.0) ? nphe_tot : NaN);
    }
    /*
        l = REC_ForwardTagger_pindex_node->getLength();
        REC_ForwardTagger_pindex_vec.resize(l);
        for (int i = 0; i < l; i++) REC_ForwardTagger_pindex_vec.at(i) = REC_ForwardTagger_pindex_node->getValue(i);

        l = REC_ForwardTagger_detector_node->getLength();
        REC_ForwardTagger_detector_vec.resize(l);
        for (int i = 0; i < l; i++) REC_ForwardTagger_detector_vec.at(i) = REC_ForwardTagger_detector_node->getValue(i);

        l = REC_ForwardTagger_energy_node->getLength();
        REC_ForwardTagger_energy_vec.resize(l);
        for (int i = 0; i < l; i++) REC_ForwardTagger_energy_vec.at(i) = REC_ForwardTagger_energy_node->getValue(i);

        l = REC_ForwardTagger_time_node->getLength();
        REC_ForwardTagger_time_vec.resize(l);
        for (int i = 0; i < l; i++) REC_ForwardTagger_time_vec.at(i) = REC_ForwardTagger_time_node->getValue(i);

        l = REC_ForwardTagger_path_node->getLength();
        REC_ForwardTagger_path_vec.resize(l);
        for (int i = 0; i < l; i++) REC_ForwardTagger_path_vec.at(i) = REC_ForwardTagger_path_node->getValue(i);

        l = REC_ForwardTagger_x_node->getLength();
        REC_ForwardTagger_x_vec.resize(l);
        for (int i = 0; i < l; i++) REC_ForwardTagger_x_vec.at(i) = REC_ForwardTagger_x_node->getValue(i);

        l = REC_ForwardTagger_y_node->getLength();
        REC_ForwardTagger_y_vec.resize(l);
        for (int i = 0; i < l; i++) REC_ForwardTagger_y_vec.at(i) = REC_ForwardTagger_y_node->getValue(i);

        l = REC_ForwardTagger_z_node->getLength();
        REC_ForwardTagger_z_vec.resize(l);
        for (int i = 0; i < l; i++) REC_ForwardTagger_z_vec.at(i) = REC_ForwardTagger_z_node->getValue(i);

        l = REC_ForwardTagger_dx_node->getLength();
        REC_ForwardTagger_dx_vec.resize(l);
        for (int i = 0; i < l; i++) REC_ForwardTagger_dx_vec.at(i) = REC_ForwardTagger_dx_node->getValue(i);

        l = REC_ForwardTagger_dy_node->getLength();
        REC_ForwardTagger_dy_vec.resize(l);
        for (int i = 0; i < l; i++) REC_ForwardTagger_dy_vec.at(i) = REC_ForwardTagger_dy_node->getValue(i);

        l = REC_ForwardTagger_radius_node->getLength();
        REC_ForwardTagger_radius_vec.resize(l);
        for (int i = 0; i < l; i++) REC_ForwardTagger_radius_vec.at(i) = REC_ForwardTagger_radius_node->getValue(i);

        l = REC_ForwardTagger_size_node->getLength();
        REC_ForwardTagger_size_vec.resize(l);
        for (int i = 0; i < l; i++) REC_ForwardTagger_size_vec.at(i) = REC_ForwardTagger_size_node->getValue(i);
    */

    len_pid = REC_Particle_pid_node->getLength();
    len_pindex = REC_Scintillator_pindex_node->getLength();

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
        int pindex = REC_Scintillator_pindex_node->getValue(k);
        int detector = REC_Scintillator_detector_node->getValue(k);

        int _sc_ftof_sec = -1;
        float _sc_ftof_time = NaN;
        float _sc_ftof_path = NaN;
        float _sc_ftof_layer = NaN;
        float _sc_ftof_energy = NaN;

        float _sc_ctof_time = NaN;
        float _sc_ctof_path = NaN;
        float _sc_ctof_energy = NaN;

        if (pindex == i && detector == 12) {
          _sc_ftof_sec = REC_Scintillator_sector_node->getValue(k);
          _sc_ftof_time = REC_Scintillator_time_node->getValue(k);
          _sc_ftof_path = REC_Scintillator_path_node->getValue(k);
          _sc_ftof_layer = REC_Scintillator_layer_node->getValue(k);
          _sc_ftof_energy = REC_Scintillator_energy_node->getValue(k);

        } else if (pindex == i && detector == 4) {
          _sc_ctof_time = REC_Scintillator_time_node->getValue(k);
          _sc_ctof_path = REC_Scintillator_path_node->getValue(k);
          _sc_ctof_energy = REC_Scintillator_energy_node->getValue(k);
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
    /*
        l = REC_Track_pindex_node->getLength();
        REC_Track_pindex_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Track_pindex_vec.at(i) = REC_Track_pindex_node->getValue(i);

        l = REC_Track_detector_node->getLength();
        REC_Track_detector_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Track_detector_vec.at(i) = REC_Track_detector_node->getValue(i);

        l = REC_Track_sector_node->getLength();
        REC_Track_sector_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Track_sector_vec.at(i) = REC_Track_sector_node->getValue(i);

        l = REC_Track_chi2_node->getLength();
        REC_Track_chi2_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Track_chi2_vec.at(i) = REC_Track_chi2_node->getValue(i);

        l = REC_Track_NDF_node->getLength();
        REC_Track_NDF_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Track_NDF_vec.at(i) = REC_Track_NDF_node->getValue(i);

        l = REC_Track_chi2_nomm_node->getLength();
        REC_Track_chi2_nomm_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Track_chi2_nomm_vec.at(i) = REC_Track_chi2_nomm_node->getValue(i);

        l = REC_Track_NDF_nomm_node->getLength();
        REC_Track_NDF_nomm_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Track_NDF_nomm_vec.at(i) = REC_Track_NDF_nomm_node->getValue(i);

        l = REC_Traj_pindex_node->getLength();
        REC_Traj_pindex_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Traj_pindex_vec.at(i) = REC_Traj_pindex_node->getValue(i);

        l = REC_Traj_detId_node->getLength();
        REC_Traj_detId_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Traj_detId_vec.at(i) = REC_Traj_detId_node->getValue(i);

        l = REC_Traj_x_node->getLength();
        REC_Traj_x_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Traj_x_vec.at(i) = REC_Traj_x_node->getValue(i);

        l = REC_Traj_y_node->getLength();
        REC_Traj_y_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Traj_y_vec.at(i) = REC_Traj_y_node->getValue(i);

        l = REC_Traj_z_node->getLength();
        REC_Traj_z_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Traj_z_vec.at(i) = REC_Traj_z_node->getValue(i);

        l = REC_Traj_cx_node->getLength();
        REC_Traj_cx_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Traj_cx_vec.at(i) = REC_Traj_cx_node->getValue(i);

        l = REC_Traj_cy_node->getLength();
        REC_Traj_cy_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Traj_cy_vec.at(i) = REC_Traj_cy_node->getValue(i);

        l = REC_Traj_cz_node->getLength();
        REC_Traj_cz_vec.resize(l);
        for (int i = 0; i < l; i++) REC_Traj_cz_vec.at(i) = REC_Traj_cz_node->getValue(i);
    */
    clas12->Fill();
    RUN_config_run_vec.clear();
    RUN_config_event_vec.clear();
    RUN_config_torus_vec.clear();
    RUN_config_solenoid_vec.clear();
    RAW_scaler_crate_vec.clear();
    RAW_scaler_slot_vec.clear();
    RAW_scaler_channel_vec.clear();
    RAW_scaler_helicity_vec.clear();
    RAW_scaler_quartet_vec.clear();
    RAW_scaler_value_vec.clear();
    REC_Event_NRUN_vec.clear();
    REC_Event_NEVENT_vec.clear();
    REC_Event_EVNTime_vec.clear();
    REC_Event_TYPE_vec.clear();
    REC_Event_TRG_vec.clear();
    REC_Event_BCG_vec.clear();
    REC_Event_STTime_vec.clear();
    REC_Event_RFTime_vec.clear();
    REC_Event_Helic_vec.clear();
    REC_Particle_pid_vec.clear();
    REC_Particle_px_vec.clear();
    REC_Particle_py_vec.clear();
    REC_Particle_pz_vec.clear();
    REC_Particle_vx_vec.clear();
    REC_Particle_vy_vec.clear();
    REC_Particle_vz_vec.clear();
    REC_Particle_charge_vec.clear();
    REC_Particle_beta_vec.clear();
    REC_Particle_chi2pid_vec.clear();
    REC_Particle_status_vec.clear();
    REC_Calorimeter_pindex_vec.clear();
    REC_Calorimeter_detector_vec.clear();
    REC_Calorimeter_sector_vec.clear();
    REC_Calorimeter_layer_vec.clear();
    REC_Calorimeter_energy_vec.clear();
    REC_Calorimeter_time_vec.clear();
    REC_Calorimeter_path_vec.clear();
    REC_Calorimeter_x_vec.clear();
    REC_Calorimeter_y_vec.clear();
    REC_Calorimeter_z_vec.clear();
    REC_Calorimeter_lu_vec.clear();
    REC_Calorimeter_lv_vec.clear();
    REC_Calorimeter_lw_vec.clear();
    REC_Cherenkov_pindex_vec.clear();
    REC_Cherenkov_detector_vec.clear();
    REC_Cherenkov_sector_vec.clear();
    REC_Cherenkov_nphe_vec.clear();
    REC_Cherenkov_time_vec.clear();
    REC_Cherenkov_path_vec.clear();
    REC_Cherenkov_theta_vec.clear();
    REC_Cherenkov_phi_vec.clear();
    REC_ForwardTagger_pindex_vec.clear();
    REC_ForwardTagger_detector_vec.clear();
    REC_ForwardTagger_energy_vec.clear();
    REC_ForwardTagger_time_vec.clear();
    REC_ForwardTagger_path_vec.clear();
    REC_ForwardTagger_x_vec.clear();
    REC_ForwardTagger_y_vec.clear();
    REC_ForwardTagger_z_vec.clear();
    REC_ForwardTagger_dx_vec.clear();
    REC_ForwardTagger_dy_vec.clear();
    REC_ForwardTagger_radius_vec.clear();
    REC_ForwardTagger_size_vec.clear();
    REC_Scintillator_pindex_vec.clear();
    REC_Scintillator_detector_vec.clear();
    REC_Scintillator_sector_vec.clear();
    REC_Scintillator_layer_vec.clear();
    REC_Scintillator_component_vec.clear();
    REC_Scintillator_energy_vec.clear();
    REC_Scintillator_time_vec.clear();
    REC_Scintillator_path_vec.clear();
    REC_Track_pindex_vec.clear();
    REC_Track_detector_vec.clear();
    REC_Track_sector_vec.clear();
    REC_Track_chi2_vec.clear();
    REC_Track_NDF_vec.clear();
    REC_Track_chi2_nomm_vec.clear();
    REC_Track_NDF_nomm_vec.clear();
    REC_Traj_pindex_vec.clear();
    REC_Traj_detId_vec.clear();
    REC_Traj_x_vec.clear();
    REC_Traj_y_vec.clear();
    REC_Traj_z_vec.clear();
    REC_Traj_cx_vec.clear();
    REC_Traj_cy_vec.clear();
    REC_Traj_cz_vec.clear();

    ec_pcal.clear();
    ec_ecin.clear();
    ec_ecout.clear();
    ec_etot.clear();
    ec_sec.clear();
    ec_time.clear();
    ec_path.clear();
    ec_x.clear();
    ec_y.clear();
    ec_z.clear();
    ec_lu.clear();
    ec_lv.clear();
    ec_lw.clear();

    cc_sec.clear();
    cc_nphe_ltcc.clear();
    cc_nphe_htcc.clear();
    cc_nphe_tot.clear();
    cc_time.clear();
    cc_path.clear();
    cc_theta.clear();
    cc_phi.clear();

    sc_ftof_sec.clear();
    sc_ftof_time.clear();
    sc_ftof_path.clear();
    sc_ftof_layer.clear();
    sc_ftof_energy.clear();

    sc_ctof_time.clear();
    sc_ctof_path.clear();
    sc_ctof_energy.clear();
  }
  OutputFile->cd();
  clas12->Write();
  OutputFile->Close();

  std::chrono::duration<double> elapsed_full = (std::chrono::high_resolution_clock::now() - start_full);
  std::cout << "Elapsed time: " << elapsed_full.count() << " s" << std::endl;
  std::cout << "Events/Sec: " << entry / elapsed_full.count() << " Hz" << std::endl;

  return 0;
}
