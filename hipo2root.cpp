
#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "TH1.h"
#include "TVector3.h"
#include "reader.h"
#include "writer.h"
#include "event.h"
#include "node.h"
#include "text.h"
#include "data.h"
#include "TTree.h"
#include "TFile.h"

using namespace std;

int main(int argc, char **argv) {

    char InFileName[128];
    char OutFileName[128];

    if (argc == 2) {
        sprintf(InFileName, "%s", argv[1]);
        sprintf(OutFileName, "%s.root", argv[1]);
        cout << OutFileName << endl;
    } else if (argc == 3) {
        sprintf(InFileName, "%s", argv[1]);
        sprintf(OutFileName, "%s", argv[2]);
    } else {
        cout << "Please provide a filename to read...." << endl;
        exit(0);
    }

    hipo::reader reader;
    reader.open(InFileName);
    TFile *OutputFile = new TFile(OutFileName, "RECREATE");
    OutputFile->SetCompressionSettings(9);
    TTree *clas12 = new TTree("clas12", "clas12");

    int size = 0;


	hipo::node<int32_t> *MC_Particle_pid_node = reader.getNode<int32_t>(20,1); 
	hipo::node<double> *MC_Particle_px_node = reader.getNode<double>(20,2); 
	hipo::node<double> *MC_Particle_py_node = reader.getNode<double>(20,3); 
	hipo::node<double> *MC_Particle_pz_node = reader.getNode<double>(20,4); 
	hipo::node<double> *MC_Particle_vx_node = reader.getNode<double>(20,5); 
	hipo::node<double> *MC_Particle_vy_node = reader.getNode<double>(20,6); 
	hipo::node<double> *MC_Particle_vz_node = reader.getNode<double>(20,7); 
	hipo::node<int32_t> *RECHB_Particle_pid_node = reader.getNode<int32_t>(22,1); 
	hipo::node<double> *RECHB_Particle_px_node = reader.getNode<double>(22,2); 
	hipo::node<double> *RECHB_Particle_py_node = reader.getNode<double>(22,3); 
	hipo::node<double> *RECHB_Particle_pz_node = reader.getNode<double>(22,4); 
	hipo::node<double> *RECHB_Particle_vx_node = reader.getNode<double>(22,5); 
	hipo::node<double> *RECHB_Particle_vy_node = reader.getNode<double>(22,6); 
	hipo::node<double> *RECHB_Particle_vz_node = reader.getNode<double>(22,7); 
	hipo::node<int> *RECHB_Particle_charge_node = reader.getNode<int>(22,8); 
	hipo::node<double> *RECHB_Particle_mass_node = reader.getNode<double>(22,9); 
	hipo::node<double> *RECHB_Particle_beta_node = reader.getNode<double>(22,10); 
	hipo::node<double> *RECHB_Particle_chi2pid_node = reader.getNode<double>(22,11); 
	hipo::node<int> *RECHB_Particle_status_node = reader.getNode<int>(22,12); 
	hipo::node<int16_t> *RECHB_Detector_index_node = reader.getNode<int16_t>(23,1); 
	hipo::node<int16_t> *RECHB_Detector_pindex_node = reader.getNode<int16_t>(23,2); 
	hipo::node<int16_t> *RECHB_Detector_detector_node = reader.getNode<int16_t>(23,3); 
	hipo::node<int16_t> *RECHB_Detector_sector_node = reader.getNode<int16_t>(23,4); 
	hipo::node<int16_t> *RECHB_Detector_layer_node = reader.getNode<int16_t>(23,5); 
	hipo::node<int16_t> *RECHB_Detector_component_node = reader.getNode<int16_t>(23,6); 
	hipo::node<double> *RECHB_Detector_x_node = reader.getNode<double>(23,7); 
	hipo::node<double> *RECHB_Detector_y_node = reader.getNode<double>(23,8); 
	hipo::node<double> *RECHB_Detector_z_node = reader.getNode<double>(23,9); 
	hipo::node<double> *RECHB_Detector_hx_node = reader.getNode<double>(23,10); 
	hipo::node<double> *RECHB_Detector_hy_node = reader.getNode<double>(23,11); 
	hipo::node<double> *RECHB_Detector_hz_node = reader.getNode<double>(23,12); 
	hipo::node<double> *RECHB_Detector_path_node = reader.getNode<double>(23,13); 
	hipo::node<double> *RECHB_Detector_time_node = reader.getNode<double>(23,14); 
	hipo::node<double> *RECHB_Detector_energy_node = reader.getNode<double>(23,15); 
	hipo::node<int32_t> *REC_Particle_pid_node = reader.getNode<int32_t>(24,1); 
	hipo::node<double> *REC_Particle_px_node = reader.getNode<double>(24,2); 
	hipo::node<double> *REC_Particle_py_node = reader.getNode<double>(24,3); 
	hipo::node<double> *REC_Particle_pz_node = reader.getNode<double>(24,4); 
	hipo::node<double> *REC_Particle_vx_node = reader.getNode<double>(24,5); 
	hipo::node<double> *REC_Particle_vy_node = reader.getNode<double>(24,6); 
	hipo::node<double> *REC_Particle_vz_node = reader.getNode<double>(24,7); 
	hipo::node<int> *REC_Particle_charge_node = reader.getNode<int>(24,8); 
	hipo::node<double> *REC_Particle_mass_node = reader.getNode<double>(24,9); 
	hipo::node<double> *REC_Particle_beta_node = reader.getNode<double>(24,10); 
	hipo::node<double> *REC_Particle_chi2pid_node = reader.getNode<double>(24,11); 
	hipo::node<int> *REC_Particle_status_node = reader.getNode<int>(24,12); 
	hipo::node<int16_t> *REC_Detector_index_node = reader.getNode<int16_t>(25,1); 
	hipo::node<int16_t> *REC_Detector_pindex_node = reader.getNode<int16_t>(25,2); 
	hipo::node<int16_t> *REC_Detector_detector_node = reader.getNode<int16_t>(25,3); 
	hipo::node<int16_t> *REC_Detector_sector_node = reader.getNode<int16_t>(25,4); 
	hipo::node<int16_t> *REC_Detector_layer_node = reader.getNode<int16_t>(25,5); 
	hipo::node<int16_t> *REC_Detector_component_node = reader.getNode<int16_t>(25,6); 
	hipo::node<double> *REC_Detector_x_node = reader.getNode<double>(25,7); 
	hipo::node<double> *REC_Detector_y_node = reader.getNode<double>(25,8); 
	hipo::node<double> *REC_Detector_z_node = reader.getNode<double>(25,9); 
	hipo::node<double> *REC_Detector_hx_node = reader.getNode<double>(25,10); 
	hipo::node<double> *REC_Detector_hy_node = reader.getNode<double>(25,11); 
	hipo::node<double> *REC_Detector_hz_node = reader.getNode<double>(25,12); 
	hipo::node<double> *REC_Detector_path_node = reader.getNode<double>(25,13); 
	hipo::node<double> *REC_Detector_time_node = reader.getNode<double>(25,14); 
	hipo::node<double> *REC_Detector_energy_node = reader.getNode<double>(25,15); 


	std::vector<int32_t> MC_Particle_pid;	std::vector<double> MC_Particle_px;	std::vector<double> MC_Particle_py;	std::vector<double> MC_Particle_pz;	std::vector<double> MC_Particle_vx;	std::vector<double> MC_Particle_vy;	std::vector<double> MC_Particle_vz;	std::vector<int32_t> RECHB_Particle_pid;	std::vector<double> RECHB_Particle_px;	std::vector<double> RECHB_Particle_py;	std::vector<double> RECHB_Particle_pz;	std::vector<double> RECHB_Particle_vx;	std::vector<double> RECHB_Particle_vy;	std::vector<double> RECHB_Particle_vz;	std::vector<int> RECHB_Particle_charge;	std::vector<double> RECHB_Particle_mass;	std::vector<double> RECHB_Particle_beta;	std::vector<double> RECHB_Particle_chi2pid;	std::vector<int> RECHB_Particle_status;	std::vector<int16_t> RECHB_Detector_index;	std::vector<int16_t> RECHB_Detector_pindex;	std::vector<int16_t> RECHB_Detector_detector;	std::vector<int16_t> RECHB_Detector_sector;	std::vector<int16_t> RECHB_Detector_layer;	std::vector<int16_t> RECHB_Detector_component;	std::vector<double> RECHB_Detector_x;	std::vector<double> RECHB_Detector_y;	std::vector<double> RECHB_Detector_z;	std::vector<double> RECHB_Detector_hx;	std::vector<double> RECHB_Detector_hy;	std::vector<double> RECHB_Detector_hz;	std::vector<double> RECHB_Detector_path;	std::vector<double> RECHB_Detector_time;	std::vector<double> RECHB_Detector_energy;	std::vector<int32_t> REC_Particle_pid;	std::vector<double> REC_Particle_px;	std::vector<double> REC_Particle_py;	std::vector<double> REC_Particle_pz;	std::vector<double> REC_Particle_vx;	std::vector<double> REC_Particle_vy;	std::vector<double> REC_Particle_vz;	std::vector<int> REC_Particle_charge;	std::vector<double> REC_Particle_mass;	std::vector<double> REC_Particle_beta;	std::vector<double> REC_Particle_chi2pid;	std::vector<int> REC_Particle_status;	std::vector<int16_t> REC_Detector_index;	std::vector<int16_t> REC_Detector_pindex;	std::vector<int16_t> REC_Detector_detector;	std::vector<int16_t> REC_Detector_sector;	std::vector<int16_t> REC_Detector_layer;	std::vector<int16_t> REC_Detector_component;	std::vector<double> REC_Detector_x;	std::vector<double> REC_Detector_y;	std::vector<double> REC_Detector_z;	std::vector<double> REC_Detector_hx;	std::vector<double> REC_Detector_hy;	std::vector<double> REC_Detector_hz;	std::vector<double> REC_Detector_path;	std::vector<double> REC_Detector_time;	std::vector<double> REC_Detector_energy;

	clas12->Branch("MC_Particle_pid",&MC_Particle_pid); 
	clas12->Branch("MC_Particle_px",&MC_Particle_px); 
	clas12->Branch("MC_Particle_py",&MC_Particle_py); 
	clas12->Branch("MC_Particle_pz",&MC_Particle_pz); 
	clas12->Branch("MC_Particle_vx",&MC_Particle_vx); 
	clas12->Branch("MC_Particle_vy",&MC_Particle_vy); 
	clas12->Branch("MC_Particle_vz",&MC_Particle_vz); 
	clas12->Branch("RECHB_Particle_pid",&RECHB_Particle_pid); 
	clas12->Branch("RECHB_Particle_px",&RECHB_Particle_px); 
	clas12->Branch("RECHB_Particle_py",&RECHB_Particle_py); 
	clas12->Branch("RECHB_Particle_pz",&RECHB_Particle_pz); 
	clas12->Branch("RECHB_Particle_vx",&RECHB_Particle_vx); 
	clas12->Branch("RECHB_Particle_vy",&RECHB_Particle_vy); 
	clas12->Branch("RECHB_Particle_vz",&RECHB_Particle_vz); 
	clas12->Branch("RECHB_Particle_charge",&RECHB_Particle_charge); 
	clas12->Branch("RECHB_Particle_mass",&RECHB_Particle_mass); 
	clas12->Branch("RECHB_Particle_beta",&RECHB_Particle_beta); 
	clas12->Branch("RECHB_Particle_chi2pid",&RECHB_Particle_chi2pid); 
	clas12->Branch("RECHB_Particle_status",&RECHB_Particle_status); 
	clas12->Branch("RECHB_Detector_index",&RECHB_Detector_index); 
	clas12->Branch("RECHB_Detector_pindex",&RECHB_Detector_pindex); 
	clas12->Branch("RECHB_Detector_detector",&RECHB_Detector_detector); 
	clas12->Branch("RECHB_Detector_sector",&RECHB_Detector_sector); 
	clas12->Branch("RECHB_Detector_layer",&RECHB_Detector_layer); 
	clas12->Branch("RECHB_Detector_component",&RECHB_Detector_component); 
	clas12->Branch("RECHB_Detector_x",&RECHB_Detector_x); 
	clas12->Branch("RECHB_Detector_y",&RECHB_Detector_y); 
	clas12->Branch("RECHB_Detector_z",&RECHB_Detector_z); 
	clas12->Branch("RECHB_Detector_hx",&RECHB_Detector_hx); 
	clas12->Branch("RECHB_Detector_hy",&RECHB_Detector_hy); 
	clas12->Branch("RECHB_Detector_hz",&RECHB_Detector_hz); 
	clas12->Branch("RECHB_Detector_path",&RECHB_Detector_path); 
	clas12->Branch("RECHB_Detector_time",&RECHB_Detector_time); 
	clas12->Branch("RECHB_Detector_energy",&RECHB_Detector_energy); 
	clas12->Branch("REC_Particle_pid",&REC_Particle_pid); 
	clas12->Branch("REC_Particle_px",&REC_Particle_px); 
	clas12->Branch("REC_Particle_py",&REC_Particle_py); 
	clas12->Branch("REC_Particle_pz",&REC_Particle_pz); 
	clas12->Branch("REC_Particle_vx",&REC_Particle_vx); 
	clas12->Branch("REC_Particle_vy",&REC_Particle_vy); 
	clas12->Branch("REC_Particle_vz",&REC_Particle_vz); 
	clas12->Branch("REC_Particle_charge",&REC_Particle_charge); 
	clas12->Branch("REC_Particle_mass",&REC_Particle_mass); 
	clas12->Branch("REC_Particle_beta",&REC_Particle_beta); 
	clas12->Branch("REC_Particle_chi2pid",&REC_Particle_chi2pid); 
	clas12->Branch("REC_Particle_status",&REC_Particle_status); 
	clas12->Branch("REC_Detector_index",&REC_Detector_index); 
	clas12->Branch("REC_Detector_pindex",&REC_Detector_pindex); 
	clas12->Branch("REC_Detector_detector",&REC_Detector_detector); 
	clas12->Branch("REC_Detector_sector",&REC_Detector_sector); 
	clas12->Branch("REC_Detector_layer",&REC_Detector_layer); 
	clas12->Branch("REC_Detector_component",&REC_Detector_component); 
	clas12->Branch("REC_Detector_x",&REC_Detector_x); 
	clas12->Branch("REC_Detector_y",&REC_Detector_y); 
	clas12->Branch("REC_Detector_z",&REC_Detector_z); 
	clas12->Branch("REC_Detector_hx",&REC_Detector_hx); 
	clas12->Branch("REC_Detector_hy",&REC_Detector_hy); 
	clas12->Branch("REC_Detector_hz",&REC_Detector_hz); 
	clas12->Branch("REC_Detector_path",&REC_Detector_path); 
	clas12->Branch("REC_Detector_time",&REC_Detector_time); 
	clas12->Branch("REC_Detector_energy",&REC_Detector_energy); 

    int nrecords = reader.getRecordCount();
    for (int event_num = 0; event_num < nrecords; event_num++) {
        cout << "[" << int(100 * event_num/nrecords) << "%]\\
" << endl;

        reader.readRecord(event_num);
        int gpart = reader.getEventCount();
        for (int i = 0; i < gpart; i++) {
            reader.readEvent(i);

            size = 0;
            size = MC_Particle_pid_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                MC_Particle_pid.push_back(MC_Particle_pid_node->getValue(s_num));
            }

            size = 0;
            size = MC_Particle_px_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                MC_Particle_px.push_back(MC_Particle_px_node->getValue(s_num));
            }

            size = 0;
            size = MC_Particle_py_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                MC_Particle_py.push_back(MC_Particle_py_node->getValue(s_num));
            }

            size = 0;
            size = MC_Particle_pz_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                MC_Particle_pz.push_back(MC_Particle_pz_node->getValue(s_num));
            }

            size = 0;
            size = MC_Particle_vx_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                MC_Particle_vx.push_back(MC_Particle_vx_node->getValue(s_num));
            }

            size = 0;
            size = MC_Particle_vy_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                MC_Particle_vy.push_back(MC_Particle_vy_node->getValue(s_num));
            }

            size = 0;
            size = MC_Particle_vz_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                MC_Particle_vz.push_back(MC_Particle_vz_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Particle_pid_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Particle_pid.push_back(RECHB_Particle_pid_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Particle_px_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Particle_px.push_back(RECHB_Particle_px_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Particle_py_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Particle_py.push_back(RECHB_Particle_py_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Particle_pz_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Particle_pz.push_back(RECHB_Particle_pz_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Particle_vx_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Particle_vx.push_back(RECHB_Particle_vx_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Particle_vy_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Particle_vy.push_back(RECHB_Particle_vy_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Particle_vz_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Particle_vz.push_back(RECHB_Particle_vz_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Particle_charge_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Particle_charge.push_back(RECHB_Particle_charge_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Particle_mass_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Particle_mass.push_back(RECHB_Particle_mass_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Particle_beta_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Particle_beta.push_back(RECHB_Particle_beta_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Particle_chi2pid_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Particle_chi2pid.push_back(RECHB_Particle_chi2pid_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Particle_status_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Particle_status.push_back(RECHB_Particle_status_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_index_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_index.push_back(RECHB_Detector_index_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_pindex_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_pindex.push_back(RECHB_Detector_pindex_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_detector_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_detector.push_back(RECHB_Detector_detector_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_sector_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_sector.push_back(RECHB_Detector_sector_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_layer_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_layer.push_back(RECHB_Detector_layer_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_component_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_component.push_back(RECHB_Detector_component_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_x_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_x.push_back(RECHB_Detector_x_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_y_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_y.push_back(RECHB_Detector_y_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_z_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_z.push_back(RECHB_Detector_z_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_hx_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_hx.push_back(RECHB_Detector_hx_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_hy_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_hy.push_back(RECHB_Detector_hy_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_hz_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_hz.push_back(RECHB_Detector_hz_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_path_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_path.push_back(RECHB_Detector_path_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_time_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_time.push_back(RECHB_Detector_time_node->getValue(s_num));
            }

            size = 0;
            size = RECHB_Detector_energy_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                RECHB_Detector_energy.push_back(RECHB_Detector_energy_node->getValue(s_num));
            }

            size = 0;
            size = REC_Particle_pid_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Particle_pid.push_back(REC_Particle_pid_node->getValue(s_num));
            }

            size = 0;
            size = REC_Particle_px_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Particle_px.push_back(REC_Particle_px_node->getValue(s_num));
            }

            size = 0;
            size = REC_Particle_py_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Particle_py.push_back(REC_Particle_py_node->getValue(s_num));
            }

            size = 0;
            size = REC_Particle_pz_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Particle_pz.push_back(REC_Particle_pz_node->getValue(s_num));
            }

            size = 0;
            size = REC_Particle_vx_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Particle_vx.push_back(REC_Particle_vx_node->getValue(s_num));
            }

            size = 0;
            size = REC_Particle_vy_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Particle_vy.push_back(REC_Particle_vy_node->getValue(s_num));
            }

            size = 0;
            size = REC_Particle_vz_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Particle_vz.push_back(REC_Particle_vz_node->getValue(s_num));
            }

            size = 0;
            size = REC_Particle_charge_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Particle_charge.push_back(REC_Particle_charge_node->getValue(s_num));
            }

            size = 0;
            size = REC_Particle_mass_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Particle_mass.push_back(REC_Particle_mass_node->getValue(s_num));
            }

            size = 0;
            size = REC_Particle_beta_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Particle_beta.push_back(REC_Particle_beta_node->getValue(s_num));
            }

            size = 0;
            size = REC_Particle_chi2pid_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Particle_chi2pid.push_back(REC_Particle_chi2pid_node->getValue(s_num));
            }

            size = 0;
            size = REC_Particle_status_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Particle_status.push_back(REC_Particle_status_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_index_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_index.push_back(REC_Detector_index_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_pindex_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_pindex.push_back(REC_Detector_pindex_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_detector_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_detector.push_back(REC_Detector_detector_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_sector_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_sector.push_back(REC_Detector_sector_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_layer_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_layer.push_back(REC_Detector_layer_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_component_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_component.push_back(REC_Detector_component_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_x_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_x.push_back(REC_Detector_x_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_y_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_y.push_back(REC_Detector_y_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_z_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_z.push_back(REC_Detector_z_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_hx_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_hx.push_back(REC_Detector_hx_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_hy_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_hy.push_back(REC_Detector_hy_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_hz_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_hz.push_back(REC_Detector_hz_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_path_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_path.push_back(REC_Detector_path_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_time_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_time.push_back(REC_Detector_time_node->getValue(s_num));
            }

            size = 0;
            size = REC_Detector_energy_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                REC_Detector_energy.push_back(REC_Detector_energy_node->getValue(s_num));
            }

        }
        clas12->Fill();
    }
OutputFile->cd();
clas12->Write();
OutputFile->Close();

return 0;
}
