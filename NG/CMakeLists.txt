Project(NationalGeographic)

Set (INSTALL_PREFIX "D:/Users/skg/Utilities")
Set (CMAKE_INSTALL_PREFIX ${INSTALL_PREFIX} CACHE INTERNAL "Installation Directory")

Include_Directories ("${CMAKE_CURRENT_SOURCE_DIR}/../../Generic/Include")
File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
	Set (ProjectName "NG Tests ${exeName}")
	Set (exeName ${exeName})
	Add_Executable(${exeName} ${file})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)
	Install (
		TARGETS ${exeName}
		RUNTIME DESTINATION bin
		)
EndForEach (file ${SOURCES})

