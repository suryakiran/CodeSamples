Project(PocoTests)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Include_Directories (
  ${Poco_INCLUDE_DIR} ${INTEL_TBB_INCLUDE_DIR}
  )

Set(PocoTargets)
ForEach (file ${SOURCES})
  Get_FileName_Component (exeName ${file} NAME_WE)
  Set (ProjectName "Poco Tests ${exeName}")
  Set (exeName poco-${exeName})
  Add_Executable(${exeName} ${file})
  List (APPEND PocoTargets ${exeName})
  Set_Target_Properties (
    ${exeName} PROPERTIES 
    PROJECT_LABEL ${ProjectName}
    )
  
  Target_Link_Libraries (
    ${exeName} ${INTEL_TBB_LIBRARIES}
    ${Poco_Foundation_LIBRARY} ${Poco_Net_LIBRARY}
    ${Poco_Util_LIBRARY} ${Poco_XML_LIBRARY}
    # optimized /usr/pic1/packages/gcc/Poco/1.5.1/lib/libPocoJSON.so
    # debug /usr/pic1/packages/gcc/Poco/1.5.1/lib/libPocoJSONd.so
    )
  Configure_Executable_File (${PYTHON_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
EndForEach (file ${SOURCES})

Add_Custom_Target (poco DEPENDS ${PocoTargets}) 
