Project(Zorba)

Include_Directories (
  ${ZORBA_INCLUDE_DIR}
  )

If (UNIX)
  Remove_Definitions("-DUNIX")
EndIf (UNIX)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
	Set (ProjectName "Zorba Tests ${exeName}")
	Set (exeName Zorba-${exeName})
	Add_Executable(${exeName} ${file})

  Target_Link_Libraries (
    ${exeName} ${ZORBA_LIBRARIES}
    )

	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)
	Add_Test (
		NAME ZorbaTests-${exeName} 
		COMMAND ${exeName} --config $<CONFIGURATION>
		)
EndForEach (file ${SOURCES})
