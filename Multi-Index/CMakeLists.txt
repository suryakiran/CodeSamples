Project(MultiIndexTests)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Include_Directories (${GenericDir}/Include)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
	Set (ProjectName "Multi-Index Tests ${exeName}")
	Set (exeName MultiIndexTests-${exeName})
	Add_Executable(${exeName} ${file})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)
	Add_Test (NAME MultiIndexTests COMMAND ${exeName})
EndForEach (file ${SOURCES})
