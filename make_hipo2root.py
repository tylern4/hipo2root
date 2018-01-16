#!/usr/bin/env python
from __future__ import print_function
import json
import pprint
import glob
import os
import argparse

# TODO: get the needed banks from config file
all_files = ["bankdefs/hipo/BST.json",
             "bankdefs/hipo/DC.json",
             "bankdefs/hipo/MC.json",
             "bankdefs/hipo/CND.json",
             "bankdefs/hipo/ECAL.json",
             "bankdefs/hipo/HTCC.json",
             "bankdefs/hipo/TOF.json",
             "bankdefs/hipo/HEADER.json",
             "bankdefs/hipo/DETECTOR.json",
             "bankdefs/hipo/FMT.json",
             "bankdefs/hipo/EVENT.json",
             "bankdefs/hipo/BMT.json",
             "bankdefs/hipo/CVT.json",
             "bankdefs/hipo/DATA.json",
             "bankdefs/hipo/FT.json",
             "bankdefs/hipo/LTCC.json"]

clas6 = ["bankdefs/hipo/CLAS6EVENT.json"]

small = ["bankdefs/hipo/EVENT.json"]

type_check = {"int8": "int",
              "int16": "int",
              "int32": "int",
              "float": "float",
              "double": "float",
              "int64": "int",
              "vector3f": "float"}


middle = """
  for (int event_num = 0; event_num < nrecords; event_num++) {
    reader.readRecord(record, event_num);
    int gpart = record.getEventCount();
    for (int i = 0; i < gpart; i++) {
      record.readHipoEvent(event, i);
"""
loop = """
    %s = event.get%s(%s, %s);
"""

ending = """
  }
  OutputFile->cd();
  clas12->Write();
  OutputFile->Close();

  return 0;
}
"""
begining = """
// Standard libs
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
// ROOT libs
#include \"TFile.h\"
#include \"TTree.h\"
#include \"TVector3.h\"
// Hipo libs
#include \"data.h\"
#include \"event.h\"
#include \"node.h\"
#include \"reader.h\"
#include \"text.h\"
#include \"writer.h\"

int main(int argc, char **argv) {

  char InFileName[128];
  char OutFileName[128];

  if (argc == 2) {
    sprintf(InFileName, \"%s\", argv[1]);
    sprintf(OutFileName, \"%s.root\", argv[1]);
    std::cout << OutFileName << std::endl;
  } else if (argc == 3) {
    sprintf(InFileName, \"%s\", argv[1]);
    sprintf(OutFileName, \"%s\", argv[2]);
  } else {
    std::cout << \"Please provide a filename to read....\" << std::endl;
    exit(0);
  }

  hipo::reader reader;
  reader.open(InFileName);
  TFile *OutputFile = new TFile(OutFileName, "RECREATE");
  OutputFile->SetCompressionSettings(9);
  TTree *clas12 = new TTree("clas12", "clas12");

  int size = 0;
  int nrecords = reader.getRecordCount();

  hipo::record record;
  hipo::event event;
"""


def make_hipo2root(files):
    root_branches = []
    root_types = []
    loops = []
    clear_vec = []
    for filename in files:
        with open(filename) as data_file:
            data = json.load(data_file)
            for bank in data:
                bank_name = str(bank["bank"])
                group = str(bank["group"])
                info = str(bank["info"])
                items = bank["items"]
                for item in items:
                    type = type_check[str(item["type"])]
                    name = bank_name.replace(
                        "::", "_") + "_" + str(item["name"])
                    loops.append(
                        loop % (name + "_vec", type.title(), group, str(item["id"])))
                    root_types.append("\tstd::vector<" +
                                      type + "> " + name + "_vec; \n")
                    root_branches.append(
                        "\t" + "clas12->Branch(\"" + name + "\",&" + name + "_vec); \n")
                    clear_vec.append("\t\t" + name + "_vec.clear();  \n")

    with open("hipo2root.cpp", 'w') as outfile:
        write = lambda x: outfile.write(x)
        write(begining)
        write("\n\n")
        map(write, root_types)
        write("\n\n")
        map(write, root_branches)
        map(write, middle)
        map(write, loops)
        write("\n\t\tclas12->Fill();\n")
        map(write, clear_vec)
        write("\n\t\t}\n")
        write(ending)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Make cpp file for converting hipo to root format')
    parser.add_argument('--json', nargs='+',
                        help='Specify json file/files for bank information, overrides all other options')
    parser.add_argument('--ALL', action='store_true',
                        help='Add all banks from bankdefs/hipo/*.json, overrides all other options')
    parser.add_argument('--clas6', action='store_true',
                        help="Add banks from clas6")
    parser.add_argument('--BST', action='store_true',
                        help='Add bank with same name')
    parser.add_argument('--DC', action='store_true',
                        help='Add bank with same name')
    parser.add_argument('--MC', action='store_true',
                        help='Add bank with same name')
    parser.add_argument('--CND', action='store_true',
                        help='Add bank with same name')
    parser.add_argument('--ECAL', action='store_true',
                        help='Add bank with same name')
    parser.add_argument('--HTCC', action='store_true',
                        help='Add bank with same name')
    parser.add_argument('--TOF', action='store_true',
                        help='Add bank with same name')
    parser.add_argument('--HEADER',
                        action='store_true', help='Add bank with same name')
    parser.add_argument('--DETECTOR',
                        action='store_true', help='Add bank with same name')
    parser.add_argument('--FMT', action='store_true',
                        help='Add bank with same name')
    parser.add_argument('--EVENT',
                        action='store_true', help='Add bank with same name')
    parser.add_argument('--BMT', action='store_true',
                        help='Add bank with same name')
    parser.add_argument('--CVT', action='store_true',
                        help='Add bank with same name')
    parser.add_argument('--DATA', action='store_true',
                        help='Add bank with same name')
    parser.add_argument('--FT', action='store_true',
                        help='Add bank with same name')
    parser.add_argument('--LTCC', action='store_true',
                        help='Add bank with same name')

    args = parser.parse_args()
    files = []
    if(args.ALL):
        files = all_files
    elif(args.json):
        files = args.json
    else:
        for arg in vars(args):
            if arg is not 'ALL' and arg is not 'json':
                if getattr(args, arg):
                    files.append('bankdefs/hipo/' + str(arg) + '.json')

    make_hipo2root(files)
