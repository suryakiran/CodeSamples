Project (CodeSamples)
CMake_Minimum_Required (VERSION 2.8.4)

Include (${CMAKE_SOURCE_DIR}/CMake/Dirs.cmake)

Include_Directories (${CMAKE_CURRENT_SOURCE_DIR})

#Include (FindPythonInterp)
#Include (FindPythonLibs)
#Include (FindPerlLibs)
Include (${CMAKE_MODULE_PATH}/Perl.cmake)

#Include (${CMAKE_MODULE_PATH}/Macros.cmake)

#Add_Subdirectory (Python)
#Add_Subdirectory (Perl)
#Add_Subdirectory (PerlNew)
Add_Subdirectory (PerlCpp)

#Write_Gvim_Search_Dirs (${PYTHON_INCLUDE_DIRS} ${PERL_INCLUDE_PATH})
Set (GvimInFile ${CMAKE_CONFIG_DIR}/gviminit.vim.in)
Set (GvimOutFile ${CMAKE_BINARY_DIR}/gviminit.vim)
Configure_File (${GvimInFile} ${GvimOutFile} @ONLY)
