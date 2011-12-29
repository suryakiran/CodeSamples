Project(OGL)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

Find_Package (Qt4 COMPONENTS QtCore QtGui QtOpenGL)
Include (${QT_USE_FILE})
Include_Directories (main ${CMAKE_CURRENT_BINARY_DIR}/main)

Set (OGL_MAIN_LIB oglmain)
Add_Subdirectory (main)

Get_Target_Property (
  OGL_MAIN_LIB_DIR ${OGL_MAIN_LIB} LOCATION
  )

Get_Filename_Component (OGL_MAIN_LIB_DIR ${OGL_MAIN_LIB_DIR} PATH)

Set (Samples 
  hello
  )

Set (OGLTargets)

ForEach (exeName ${Samples})
  String (CONFIGURE ${dir_tmpl} dir @ONLY)

  Set (mainFile ${CMAKE_CURRENT_BINARY_DIR}/${exeName}_main.cxx)

  Execute_Perl (
    FILE ${PL_FILE_CASE_CONV}
    ARGS
    -i ${exeName}_window
    -t camel_case
    -d _
    OUTPUT WindowName
    )
  Configure_File (
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cxx.in
    ${mainFile}
    @ONLY
    )

  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  File (GLOB HPP_FILES ${dir}/*.hpp)

  Set (ProjectName "OGL Tests ${exeName}")
  Set (exeName ogl-${exeName})

  Include_Directories (${dir})
  Add_Executable(${exeName} ${mainFile} ${CPP_FILES} ${H_FILES} ${HPP_FILES})

	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)

    Target_Link_Libraries (
      ${exeName} ${OGL_MAIN_LIB}
      )

  List (APPEND OGLTargets ${exeName})
  Get_Target_Property (CURRENT_EXE_FILE ${exeName} LOCATION)

  Process_Perl_Template (
    PERL_FILE ${PL_FILE_SAMPLES_EXE}
    TEMPLATE ${CMAKE_SAMPLES_TMPL}
    OUTPUT ${CMAKE_BINARY_DIR}/${exeName}
    ARGS -e ${exeName} -d ${OGL_MAIN_LIB_DIR}
    )
EndForEach (file ${SOURCES})

Add_Custom_Target (ogl DEPENDS ${OGLTargets}) 
