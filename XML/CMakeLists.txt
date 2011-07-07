Project(XML)

Include (${CMAKE_MODULE_PATH}/Xerces.cmake)
Include (${CMAKE_MODULE_PATH}/Xqilla.cmake)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)
Set (PERL_OUT_FILE ${CMAKE_BINARY_DIR}/xquery-xpath)

Include_Directories (
  ${XERCES_INCLUDE_DIR}
  ${XQILLA_INCLUDE_DIR}
  )

Set (XmlTargets)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)
  Include_Directories (${dir})
  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  Set (ProjectName "XML Tests ${exeName}")
  Set (exeName XML-${exeName})
  Add_Executable(${exeName} ${file} ${CPP_FILES} ${H_FILES})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)

  Target_Link_Libraries (
    ${exeName}
    ${XERCES_LIBRARIES} ${XQILLA_LIBRARIES}
    ${ParseArgsLib}
    )

  List (APPEND XmlTargets ${exeName})
  Get_Target_Property (CURRENT_EXE_FILE ${exeName} LOCATION)
  Configure_Executable_File (${PERL_IN_FILE} ${PERL_OUT_FILE} @ONLY)

EndForEach (file ${SOURCES})

Add_Custom_Target (xml DEPENDS ${XmlTargets}) 
