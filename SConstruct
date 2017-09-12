#=================================================
# The SCONSTRUCT file for building HIPO project.
#
#=================================================
import glob
import os
import sys
from make_hipo2root import make_hipo2root
#=================================================
# LOADING THE ENVIRONMENT
#=================================================
env = Environment(CPPPATH=[".", "include"])

env.Append(ENV = os.environ)
env.Append(CCFLAGS=["-O2","-fPIC","-m64","-fmessage-length=0","-g","-std=c++14"])
make_hipo2root()
#=================================================
# Check for compression libraries.
#=================================================
conf = Configure(env)
if conf.CheckLib('liblz4'):
    env.Append(CCFLAGS="-D__LZ4__")
if conf.CheckLib('libz'):
    env.Append(CCFLAGS="-D__LIBZ__")

#=================================================
#
#=================================================
codeList_CPP  = glob.glob('libcpp/*.cpp')
lib   = env.SharedLibrary(target="libcpp/libhipo.so", source = codeList_CPP)

make_hipo2root()
