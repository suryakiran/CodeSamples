Project(Perl)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File (GLOB CXX_FILES *.cxx)
File (GLOB C_FILES *.c)
File (GLOB COMMON_FILES *.h)

Include_Directories (${PERL_INCLUDE_PATH})

Set (PERL_XSI_FILE ${CMAKE_CURRENT_BINARY_DIR}/perlxsi.c)

Add_Custom_Command (
  OUTPUT ${PERL_XSI_FILE}
  COMMAND ${PERL_EXECUTABLE} -MExtUtils::Embed -e xsinit -- Test
  )

ForEach (cf ${CXX_FILES} ${C_FILES})
  Get_Filename_Component (exeName ${cf} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)
  Include_Directories (${dir})
  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  Add_Executable (${exeName} ${cf} ${CPP_FILES} ${H_FILES} ${COMMON_FILES}
    ${PERL_XSI_FILE})
  Set_Target_Properties (${exeName} PROPERTIES 
    COMPILE_DEFINITIONS "FILES_DIR=\"${dir}\""
    )
  Target_Link_Libraries (${exeName} ${PERL_LIBRARY})
  Set_Property (TARGET ${exeName} PROPERTY FOLDER "Perl Embed Samples")
EndForEach (cf)
