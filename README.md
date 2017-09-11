# hipo2root

Conversion program from hipo to root format.

## To build:

```
git clone https://github.com/tylern4/hipo2root.git
cd hipo2root
scons
make
```
## To use

```
./hipo2root infile.hipo outfile.root
```

## TODO

* Allow bank configuration with file.
* Add banks to directories.
* Check branch types are converted properly:
  - Look into "vector3f" typed branches
* Look into  fixing:
  - "note: variable tracking size limit exceeded with -fvar-tracking-assignments, retrying without"
