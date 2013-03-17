Project(MplTests)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set(MplTargets)
ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
	Set (ProjectName "Mpl Tests ${exeName}")
	Set (exeName mpl-${exeName})
	Add_Executable(${exeName} ${file})
        List (APPEND MplTargets ${exeName})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)
  Configure_Executable_File (${PYTHON_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
EndForEach (file ${SOURCES})

Add_Custom_Target (mpl DEPENDS ${MplTargets}) 
