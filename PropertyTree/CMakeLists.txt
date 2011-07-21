Project(PropertyTree)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
	Set (ProjectName "PropertyTree Tests ${exeName}")
	Set (exeName PropertyTree-${exeName})
	Add_Executable(${exeName} ${file})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)
EndForEach (file ${SOURCES})
