#=================================================
# The SCONSTRUCT file for building HIPO project.
#
#=================================================
import glob
import os
import sys

#=================================================
# LOADING THE ENVIRONMENT
#=================================================
env = Environment(CPPPATH=[".", "include"])

env.Append(ENV = os.environ)
env.Append(CCFLAGS=["-O2","-fPIC","-m64","-fmessage-length=0","-g"])

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
lib   = env.Library(target="libcpp/libhipo.o", source = codeList_CPP)
