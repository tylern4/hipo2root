# hipo2root

Conversion program from hipo to root format.

## To build:

    git clone --recurse-submodules https://github.com/tylern4/hipo2root.git
    cd hipo2root
    # Use ./make_hipo2root.py --help for more options
    # Look below on how to define your own bank structure
    ./make_hipo2root.py
    make

## Choosing banks:

To choose which banks you would like, instead of copying over all the banks you can use a json file to define which banks you use. There is an example in bankdefs/rec_particle.json. To build with specific banks just run:

    ./make_hipo2root.py --json bankdefs/rec_particle.json
    make

## To use

    ./hipo2root infile.hipo outfile.root

## TODO

-   [x] Allow bank configuration with file.
-   [x] Add banks to directories.
-   [ ] Look into  fixing:
    -   "note: variable tracking size limit exceeded with -fvar-tracking-assignments, retrying without"
