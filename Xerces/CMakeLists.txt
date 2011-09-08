Project(Xerces)

Include_Directories (
  ${XERCES_INCLUDE_DIR}
  )

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
	Set (ProjectName "Xerces Tests ${exeName}")
	Set (exeName Xerces-${exeName})
	Add_Executable(${exeName} ${file})

  Target_Link_Libraries (
    ${exeName} ${XERCES_LIBRARIES}
    )

	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)
	Add_Test (
		NAME XercesTests-${exeName} 
		COMMAND ${exeName} --config $<CONFIGURATION>
		)
EndForEach (file ${SOURCES})
