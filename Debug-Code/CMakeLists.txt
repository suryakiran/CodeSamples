Project(DebugTests)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set(DebugTargets)
ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
	Set (ProjectName "Debug Tests ${exeName}")
	Set (exeName debug-${exeName})
	Add_Executable(${exeName} ${file})
        List (APPEND DebugTargets ${exeName})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)
  Configure_Executable_File (${PYTHON_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
EndForEach (file ${SOURCES})

Add_Custom_Target (debug DEPENDS ${DebugTargets}) 
