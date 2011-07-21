Project(Xpressive)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
	Set (ProjectName "Xpressive Tests ${exeName}")
	Set (exeName Xpressive-${exeName})
	Add_Executable(${exeName} ${file})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)
	Add_Test (
		NAME XpressiveTests-${exeName} 
		COMMAND ${exeName} --config $<CONFIGURATION>
		)
EndForEach (file ${SOURCES})
