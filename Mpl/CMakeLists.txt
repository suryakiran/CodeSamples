Project(Mpl)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
  Set (ProjectName "Mpl Tests ${exeName}")
  Set (exeName Mpl-${exeName})
	Add_Executable(${exeName} ${file})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)
	Add_Test (
    NAME MplTests-${exeName} 
		COMMAND ${exeName} --config $<CONFIGURATION>
		)
EndForEach (file ${SOURCES})
