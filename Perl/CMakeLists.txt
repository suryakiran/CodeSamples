Project(Perl)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File (GLOB CXX_FILES *.cxx)
File (GLOB C_FILES *.c)
File (GLOB COMMON_FILES *.h)

Include_Directories (${PERL_INCLUDE_PATH})

ForEach (cf ${CXX_FILES} ${C_FILES})
  Get_Filename_Component (exeName ${cf} NAME_WE)
  Set (exeName perl-${exeName})
  String (CONFIGURE ${dir_tmpl} dir @ONLY)
  Include_Directories (${dir})
  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  Add_Executable (${exeName} ${cf} ${CPP_FILES} ${H_FILES} ${COMMON_FILES})
  Set_Target_Properties (${exeName} PROPERTIES 
    COMPILE_DEFINITIONS "FILES_DIR=\"${dir}\""
    )
  Target_Link_Libraries (${exeName} ${PERL_LIBRARY} ${ParseArgsLib} ${Boost_FILESYSTEM_LIBRARY})
  Set_Property (TARGET ${exeName} PROPERTY FOLDER "Perl Embed Samples")
  CodeSamples_Create_Wrapper (${exeName})
EndForEach (cf)
