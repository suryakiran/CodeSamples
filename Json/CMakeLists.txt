Project(JSON)

cmake_minimum_required(VERSION 3.3)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set (JSONTargets)
Find_Package(PkgConfig)
Pkg_check_modules(Json jsoncpp)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)

  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  File (GLOB HPP_FILES ${dir}/*.hpp)

  Set (ProjectName "JSON Tests ${exeName}")
  Set (exeName json-${exeName})

  Include_Directories (${dir} ${Json_INCLUDE_DIRS})
  Add_Executable(${exeName} ${file} ${CPP_FILES} ${H_FILES} ${HPP_FILES})

	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)

  Target_Link_Libraries (
    ${exeName} ${Boost_THREAD_LIBRARY} ${Json_LIBRARIES}
    )
  
  Target_compile_features (${exeName} PRIVATE cxx_range_for)

  List (APPEND JSONTargets ${exeName})
  # Get_Target_Property (CURRENT_EXE_FILE ${exeName} LOCATION)
  # Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)

EndForEach (file ${SOURCES})

Add_Custom_Target (json DEPENDS ${JSONTargets}) 
