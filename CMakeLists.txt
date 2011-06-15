Project (CodeSamples)
CMake_Minimum_Required (VERSION 2.8.4)

Set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
Set (CONFIG_DIR ${CMAKE_SOURCE_DIR}/Config)
Include_Directories (${CMAKE_CURRENT_SOURCE_DIR})

#Include (FindPythonInterp)
#Include (FindPythonLibs)
Include (FindPerlLibs)

#Include (${CMAKE_MODULE_PATH}/Macros.cmake)

#Add_Subdirectory (Python)
Add_Subdirectory (Perl)

#Write_Gvim_Search_Dirs (${PYTHON_INCLUDE_DIRS} ${PERL_INCLUDE_PATH})
Set (GvimInFile ${CONFIG_DIR}/gviminit.vim.in)
Set (GvimOutFile ${CMAKE_BINARY_DIR}/gviminit.vim)
Configure_File (${GvimInFile} ${GvimOutFile} @ONLY)
