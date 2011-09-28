Project(XML)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set (SignalsTargets)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)
  Include_Directories (${dir})
  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  Set (ProjectName "Signals Tests ${exeName}")
  Set (exeName Signals-${exeName})
  Add_Executable(${exeName} ${file} ${CPP_FILES} ${H_FILES})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)

  List (APPEND SignalsTargets ${exeName})
  Get_Target_Property (CURRENT_EXE_FILE ${exeName} LOCATION)
  Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)

EndForEach (file ${SOURCES})

Add_Custom_Target (signals DEPENDS ${SignalsTargets}) 
