Project(Python)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exe_name@_files)

File (GLOB CXX_FILES *.cxx)
File (GLOB C_FILES *.c)
File (GLOB COMMON_FILES *.h)

Include_Directories (${PERL_INCLUDE_PATH})

Execute_Process (
  COMMAND
  ${PERL_EXECUTABLE} -MExtUtils::Embed -e ccopts
  OUTPUT_VARIABLE PERL_CCOPTS
  )

Execute_Process (
  COMMAND
  ${PERL_EXECUTABLE} -MExtUtils::Embed -e ldopts
  OUTPUT_VARIABLE PERL_LDOPTS
  )

ForEach (cf ${CXX_FILES} ${C_FILES})
  Get_Filename_Component (exe_name ${cf} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)
  Include_Directories (${dir})
  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  Add_Executable (${exe_name} ${cf} ${CPP_FILES} ${H_FILES} ${COMMON_FILES})
  Set_Target_Properties (${exe_name} PROPERTIES 
    COMPILE_DEFINITIONS "FILES_DIR=\"${dir}\""
    )
  Target_Link_Libraries (${exe_name} ${PERL_LIBRARY})
EndForEach (cf)
