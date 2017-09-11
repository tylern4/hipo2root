#!/usr/bin/env python
from __future__ import print_function
import json
import pprint
import glob
import os


# TODO: get the needed banks from config file
files = ["bankdefs/hipo/ECAL.json", "bankdefs/hipo/EVENT.json",
         "bankdefs/hipo/TOF.json", "bankdefs/hipo/DC.json",
         "bankdefs/hipo/CVT.json", "bankdefs/hipo/SVT.json"]

# TODO: Make sure all types are being converted properly
type_check = {"int8": "int",
              "int16": "int16_t",
              "int32": "int32_t",
              "float": "double",
              "int64": "Int_t",
              "vector3f": "TVector3"}

begining = """
//Standard libs
#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>
//ROOT libs
#include "TH1.h"
#include "TVector3.h"
#include "TTree.h"
#include "TFile.h"
//Hipo libs
#include "reader.h"
#include "writer.h"
#include "event.h"
#include "node.h"
#include "text.h"
#include "data.h"


using namespace std;

int main(int argc, char **argv) {

    char InFileName[128];
    char OutFileName[128];

    if (argc == 2) {
        sprintf(InFileName, \"%s\", argv[1]);
        sprintf(OutFileName, \"%s.root\", argv[1]);
        cout << OutFileName << endl;
    } else if (argc == 3) {
        sprintf(InFileName, \"%s\", argv[1]);
        sprintf(OutFileName, \"%s\", argv[2]);
    } else {
        cout << \"Please provide a filename to read....\" << endl;
        exit(0);
    }

    hipo::reader reader;
    reader.open(InFileName);
    TFile *OutputFile = new TFile(OutFileName, "RECREATE");
    OutputFile->SetCompressionSettings(9);
    TTree *clas12 = new TTree("clas12", "clas12");
"""

middle = """
    int size = 0;
    int nrecords = reader.getRecordCount();
    for (int event_num = 0; event_num < nrecords; event_num++) {
        //cout << \"[\" << int(100 * event_num/nrecords) << \"%]\" << endl;

        reader.readRecord(event_num);
        int gpart = reader.getEventCount();
        for (int i = 0; i < gpart; i++) {
            reader.readEvent(i);
"""
loop = """
            size = 0;
            size = %s_node->getLength();
            for (int s_num = 0; s_num < size; s_num++) {
                %s.push_back(%s_node->getValue(s_num));
            }
"""

ending = """
    }
    OutputFile->cd();
    clas12->Write();
    OutputFile->Close();

    return 0;
}
"""


def make_hipo2root():
    hipo_nodes = []
    root_branches = []
    root_types = []
    loops = []
    clear_vec = []
    for filename in files:
        with open(filename) as data_file:
            data = json.load(data_file)

            for bank in data:
                # pprint.pprint(bank)
                bank_name = str(bank["bank"])
                group = str(bank["group"])
                info = str(bank["info"])
                # print("/* \n", group, "\n", bank_name, "\n", info, "\n*/ \n")
                items = bank["items"]
                for item in items:
                    type = type_check[str(item["type"])]

                    name = bank_name.replace(
                        "::", "_") + "_" + str(item["name"])

                    loops.append(loop % (name, name, name))
                    hipo_nodes.append("\t" + "hipo::node<" + type + "> *" + name +
                                      "_node = reader.getNode<" + type +
                                      ">(" + group + "," + str(item["id"]) + "); \n")
                    root_types.append("\tstd::vector<" +
                                      type + "> " + name + ";  \n")
                    root_branches.append("\t" + "clas12->Branch(\"" +
                                         name + "\",&" + name + "); \n")
                    clear_vec.append("\t\t" + name + ".clear();  \n")

    with open("hipo2root.cpp", 'w') as outfile:
        write = lambda x: outfile.write(x)
        write(begining)
        write("\n\n")
        map(write, hipo_nodes)
        write("\n\n")
        map(write, root_types)
        write("\n\n")
        map(write, root_branches)
        map(write, middle)
        map(write, loops)
        write("\n\t\tclas12 -> Fill();\n")
        map(write, clear_vec)
        write("\n\t\t}\n")
        write(ending)

if __name__ == '__main__':
    make_hipo2root()
