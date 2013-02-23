Project(YamlTests)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set(YamlTargets)
Include_Directories (${YAML_CPP_INCLUDE_DIR})
ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
	Set (ProjectName "Yaml Tests ${exeName}")
	Set (exeName yaml-${exeName})
	Add_Executable(${exeName} ${file})
        List (APPEND YamlTargets ${exeName})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)
        Target_Link_Libraries (
          ${exeName}
          ${YAML_CPP_LIBRARIES}
          ${ParseArgsLib}
          ${Boost_FILESYSTEM_LIBRARY}
          )
  Configure_Executable_File (${PYTHON_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
EndForEach (file ${SOURCES})

Add_Custom_Target (yaml DEPENDS ${YamlTargets}) 
