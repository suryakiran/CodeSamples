Project(TbbTests)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set(TbbTargets)
ForEach (file ${SOURCES})
  Get_FileName_Component (exeName ${file} NAME_WE)
  Set (ProjectName "Tbb Tests ${exeName}")
  Set (exeName tbb-${exeName})
  Add_Executable(${exeName} ${file})
  List (APPEND TbbTargets ${exeName})
  Set_Target_Properties (
    ${exeName} PROPERTIES 
    PROJECT_LABEL ${ProjectName}
    )
  Target_Link_Libraries (
    ${exeName}
    ${INTEL_TBB_LIBRARIES}
    ${INTEL_TBB_MALLOC_LIBRARIES}
    ${INTEL_TBB_MALLOC_PROXY_LIBRARIES}
    )
  Configure_Executable_File (${PYTHON_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
EndForEach (file ${SOURCES})

Add_Custom_Target (tbb DEPENDS ${TbbTargets}) 
