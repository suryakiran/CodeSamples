Project(RestTests)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Find_Package(CURL)
Include_Directories (
  ${CURL_INCLUDE_DIR} ${INTEL_TBB_INCLUDE_DIR}
  )
Set(RestTargets)
ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
	Set (ProjectName "Rest Tests ${exeName}")
	Set (exeName rest-${exeName})
	Add_Executable(${exeName} ${file})
        List (APPEND RestTargets ${exeName})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)
              
        Target_Link_Libraries (
          ${exeName} ${CURL_LIBRARIES}
          ${Boost_THREAD_LIBRARIES} ${Boost_SYSTEM_LIBRARIES}
          ${INTEL_TBB_LIBRARIES}
          )
  Configure_Executable_File (${PYTHON_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
EndForEach (file ${SOURCES})

Add_Custom_Target (rest DEPENDS ${RestTargets}) 
