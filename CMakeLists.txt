Project (CodeSamples)

CMake_Minimum_Required (VERSION 2.8.4)
Include (${CMAKE_SOURCE_DIR}/CMake/Config.cmake)
Include_Cmake_Module(Perl)

If (UNIX)
	Add_Definitions ("-DUNIX")
Else (UNIX)
	Add_Definitions ("-DWINDOWS")
	Add_Definitions ("-DBOOST_TYPEOF_SILENT")
	Add_Definitions ("-DBOOST_ALL_DYN_LINK")
	If (${CMAKE_SYSTEM_VERSION} EQUAL 6.0)
		Add_Definitions ("-DWIN_VISTA")
	EndIf (${CMAKE_SYSTEM_VERSION} EQUAL 6.0)
EndIf (UNIX)

Include (${CMAKE_MODULE_PATH}/Perl.cmake)
Include (${CMAKE_MODULE_PATH}/Macros.cmake)
Include (${CMAKE_MODULE_PATH}/Targets.cmake)
Include (${CMAKE_MODULE_PATH}/Compiler.cmake)
Include (${CMAKE_MODULE_PATH}/Xerces.cmake)
Include (${CMAKE_MODULE_PATH}/Zorba.cmake)

If (NOT CMAKE_BUILD_TYPE)
  Set (CMAKE_BUILD_TYPE "Debug")
EndIf (NOT CMAKE_BUILD_TYPE)

Set(Boost_ADDITIONAL_VERSIONS "1.47")
Find_Package (
  Boost
  COMPONENTS date_time program_options filesystem system
  )

Include_Directories (${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
Link_Directories    (${Boost_LIBRARY_DIRS})

Set (ParseArgsLib "parse_args")
Include_Directories (${CMAKE_SOURCE_DIR}/CommandLineArgs)
Add_Subdirectory (CommandLineArgs)

Macro (ADD_SUBDIRECTORY_IF p_varName p_dirName)
  If (${p_varName})
    Add_Subdirectory (${p_dirName})
  EndIf (${p_varName})
EndMacro (ADD_SUBDIRECTORY_IF)

OPTION (BUILD_SAMPLES_MULTI_INDEX "Build Multi Index Samples" FALSE)
OPTION (BUILD_SAMPLES_FUSION "Build Fusion Samples" FALSE)
OPTION (BUILD_SAMPLES_FILE_READING "Build File Reading Samples" FALSE)
OPTION (BUILD_SAMPLES_MISCELLANEOUS "Build Miscellaneous Samples" FALSE)
OPTION (BUILD_SAMPLES_NG "Build NG Samples" FALSE)
OPTION (BUILD_SAMPLES_PREPROCESSOR "Build PreProcessor Samples" FALSE)
OPTION (BUILD_SAMPLES_PHOENIX "Build Phoenix Samples" FALSE)
OPTION (BUILD_SAMPLES_SPIRIT "Build Spirit Samples" FALSE)
OPTION (BUILD_SAMPLES_PROPERTY_TREE "Build Property Tree Samples" FALSE)
OPTION (BUILD_SAMPLES_HOLIDAYS "Build Holidays Samples" FALSE)
OPTION (BUILD_SAMPLES_TEMPLATES "Build Templates Samples" FALSE)
OPTION (BUILD_SAMPLES_CPP "Build CPP Samples" FALSE)
OPTION (BUILD_SAMPLES_DOWNLOAD_FILE "Build Download File Samples" FALSE)
OPTION (BUILD_SAMPLES_PERL "Build Perl Samples" FALSE)
OPTION (BUILD_SAMPLES_PERL_CPP "Build Perl Cpp Samples" FALSE)
OPTION (BUILD_SAMPLES_XML "Build XML Samples" FALSE)
OPTION (BUILD_SAMPLES_MPL "Build MPL Samples" FALSE)
OPTION (BUILD_SAMPLES_XERCES "Build Xerces Samples" FALSE)
OPTION (BUILD_SAMPLES_ZORBA "Build Zorba Samples" FALSE)
OPTION (BUILD_SAMPLES_SIGNALS "Build Signals Samples" FALSE)

Add_Subdirectory_If (BUILD_SAMPLES_MULTI_INDEX Multi-Index)
Add_Subdirectory_If (BUILD_SAMPLES_FUSION Fusion)
Add_Subdirectory_If (BUILD_SAMPLES_FILE_READING FileReading)
Add_Subdirectory_If (BUILD_SAMPLES_MISCELLANEOUS Miscellaneous)
Add_Subdirectory_If (BUILD_SAMPLES_NG NG)
Add_Subdirectory_If (BUILD_SAMPLES_PREPROCESSOR PreProcessor)
Add_Subdirectory_If (BUILD_SAMPLES_PHOENIX Phoenix)
Add_Subdirectory_If (BUILD_SAMPLES_SPIRIT Spirit)
Add_Subdirectory_If (BUILD_SAMPLES_PROPERTY_TREE PropertyTree)
Add_Subdirectory_If (BUILD_SAMPLES_HOLIDAYS Holidays)
Add_Subdirectory_If (BUILD_SAMPLES_TEMPLATES Templates)
Add_Subdirectory_If (BUILD_SAMPLES_CPP CPP)
Add_Subdirectory_If (BUILD_SAMPLES_DOWNLOAD_FILE DownloadFile)
Add_Subdirectory_If (BUILD_SAMPLES_PERL Perl)
Add_Subdirectory_If (BUILD_SAMPLES_PERL_CPP PerlCpp)
Add_Subdirectory_If (BUILD_SAMPLES_XML XML)
Add_Subdirectory_If (BUILD_SAMPLES_MPL Mpl)
Add_Subdirectory_If (BUILD_SAMPLES_XERCES Xerces)
Add_Subdirectory_If (BUILD_SAMPLES_ZORBA Zorba)
Add_Subdirectory_If (BUILD_SAMPLES_SIGNALS Signals)

Find_File (
  PERL_IN_FILE
    test.pl.in
  PATHS
    ${CMAKE_SOURCE_DIR}
  )

Cmake_List_To_Perl_Args (AdditionalGvimSearchDirs -d ${IncludeDirectories})
Cmake_List_To_Perl_Args (ProjectModules -p ${PROJECT_MODULES})

Process_Perl_Template (
  PERL_FILE ${PL_FILE_GVIM_INIT}
  TEMPLATE ${CMAKE_GVIM_INIT_TMPL_FILE}
  OUTPUT ${CMAKE_GVIM_INIT_FILE_OUT}
  ARGS ${AdditionalGvimSearchDirs} ${ProjectModules}
  )
