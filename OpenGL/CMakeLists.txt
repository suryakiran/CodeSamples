Project(OGL)

Find_Package (GLUT)
Find_Package (OpenGL)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set (OGLTargets)
Include_Directories (${GLUT_INCLUDE_DIR})

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)

  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  File (GLOB HPP_FILES ${dir}/*.hpp)

  Set (ProjectName "OGL Tests ${exeName}")
  Set (exeName ogl-${exeName})

  Include_Directories (${dir})
  Add_Executable(${exeName} ${file} ${CPP_FILES} ${H_FILES} ${HPP_FILES})

  Target_Link_Libraries (
    ${exeName} ${OPENGL_gl_LIBRARY} ${GLUT_glut_LIBRARY} ${OPENGL_glu_LIBRARY}
    )
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)

  List (APPEND OGLTargets ${exeName})
  Get_Filename_Component (GLUT_BIN_DIR ${GLUT_INCLUDE_DIR} PATH)
  Set (GLUT_BIN_DIR ${GLUT_BIN_DIR}/bin)

  IF (UNIX)
    Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
  Else (UNIX)
    Create_Vcxproj_User_File (${exeName} --lib-dir ${GLUT_BIN_DIR})
  EndIf (UNIX)

EndForEach (file ${SOURCES})

Add_Custom_Target (ogl DEPENDS ${OGLTargets}) 
