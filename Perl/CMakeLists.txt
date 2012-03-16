Project(Python)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exe_name@_files)

File (GLOB CXX_FILES *.cxx)
File (GLOB C_FILES *.c)
File (GLOB COMMON_FILES *.h)

Include_Directories (${PERL_INCLUDE_PATH})
Set (PERL_C_MODULES IO Fcntl B Socket Encode HTML::Parser Data::Dumper)
Find_Perl_C_Modules (${PERL_C_MODULES})

Set (PERL_XSI_FILE ${CMAKE_CURRENT_BINARY_DIR}/perlxsi.c)

Add_Custom_Command (
  OUTPUT ${PERL_XSI_FILE}
  COMMAND ${PERL_EXECUTABLE} -MExtUtils::Embed -e xsinit -- ${PERL_C_MODULES}
  )
Get_Property (PERL_C_MODULE_PATHS GLOBAL PROPERTY PERL_C_MODULE_PATHS) 
Cmake_List_To_Perl_Args (PerlCModulePaths --lib-dir ${PERL_C_MODULE_PATHS})

ForEach (cf ${CXX_FILES} ${C_FILES})
  Get_Filename_Component (exe_name ${cf} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)
  Include_Directories (${dir})
  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  Add_Executable (${exe_name} ${cf} ${CPP_FILES} ${H_FILES} ${COMMON_FILES}
    ${PERL_XSI_FILE})
  Set_Target_Properties (${exe_name} PROPERTIES 
    COMPILE_DEFINITIONS "FILES_DIR=\"${dir}\""
    )
  Target_Link_Libraries (${exe_name} ${PERL_LIBRARY})
  Perl_Xsi_Depends (${exe_name} ${PERL_C_MODULES})
  If (WIN32)
    Execute_Perl (
      FILE 
        ${PL_FILE_VCXPROJ_USER_FILE}
      ARGS 
        -o ${CMAKE_CURRENT_BINARY_DIR}/${exe_name}.vcxproj.user
        -x ${CMAKE_VARIABLES_XML_OUT_FILE}
        -e ${exe_name}
        ${PerlCModulePaths}
      )
  EndIf (WIN32)
EndForEach (cf)
