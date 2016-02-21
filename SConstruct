import os, sys

subdirs = ['Boost']

env = Environment()
env.Append(
    CPPPATH = [
        os.getcwd(),
        '/usr/local/boost/1.60.0/include/boost-1_60',
    ],
    LIBPATH = [
        '/usr/local/boost/1.60.0/lib',
    ],
)
for d in subdirs:
    SConscript(os.path.join(d, 'SConscript'), exports = ['env'])
