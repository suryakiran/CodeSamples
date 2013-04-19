Project(BoostTests)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set(BoostTargets)
ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
	Set (ProjectName "Boost Tests ${exeName}")
	Set (exeName boost-${exeName})
	Add_Executable(${exeName} ${file})
        List (APPEND BoostTargets ${exeName})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)
              Target_Link_Libraries (
                ${exeName}
                ${ParseArgsLib}
                ${Boost_IOSTREAMS_LIBRARY}
                )
  Configure_Executable_File (${PYTHON_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
EndForEach (file ${SOURCES})

Add_Custom_Target (boost DEPENDS ${DebugTargets}) 
