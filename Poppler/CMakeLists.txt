Project(Poppler)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set (PopplerTargets)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)

  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  File (GLOB HPP_FILES ${dir}/*.hpp)

  Set (ProjectName "Poppler Tests ${exeName}")
  Set (exeName poppler-${exeName})

  Include_Directories (${dir})
  Add_Executable(${exeName} ${file} ${Poppler_FILES} ${H_FILES} ${HPP_FILES})

  Set_Target_Properties (
    ${exeName} PROPERTIES 
    PROJECT_LABEL ${ProjectName}
    )

  Target_Link_Libraries (
    ${exeName} ${POPPLER_CPP_LIBRARIES}
    )

  List (APPEND PopplerTargets ${exeName})
  Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)

EndForEach (file ${SOURCES})

Add_Custom_Target (poppler DEPENDS ${PopplerTargets}) 
