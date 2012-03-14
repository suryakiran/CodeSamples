Project(GEOM)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

Include_Directories (${CMAKE_CURRENT_SOURCE_DIR})
File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set (GEOMTargets)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)

  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  File (GLOB HPP_FILES ${dir}/*.hpp)

  Set (ProjectName "GEOM Tests ${exeName}")
  Set (exeName geo-${exeName})

  Include_Directories (${dir})
  Add_Executable(${exeName} ${file} ${CPP_FILES} ${H_FILES} ${HPP_FILES})

	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)

  List (APPEND GEOMTargets ${exeName})
  Get_Target_Property (CURRENT_EXE_FILE ${exeName} LOCATION)
  Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)

EndForEach (file ${SOURCES})

Add_Custom_Target (geo DEPENDS ${GEOMTargets}) 
