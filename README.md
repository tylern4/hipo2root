# hipo2root

Conversion program from hipo to root format.

## To build:

```
git clone https://github.com/tylern4/hipo2root.git
cd hipo2root
./make_hipo2root.py
make
```

## To use
```
./hipo2root infile.hipo outfile.root
```

## TODO

- [x] Allow bank configuration with file.
- [x] Add banks to directories.
- [ ] Look into  fixing:
    - "note: variable tracking size limit exceeded with -fvar-tracking-assignments, retrying without"
