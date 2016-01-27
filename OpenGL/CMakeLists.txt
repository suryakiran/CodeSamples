Project(OGL)

Set (CMAKE_SKIP_BUILD_RPATH FALSE)
Set (OPENGL_LIB "OpenGLLib")
Set (OPENGL_LIB_SRC_DIR "" PARENT_SCOPE)

Add_Subdirectory(lib)

Include_Directories (${CMAKE_CURRENT_SOURCE_DIR}/lib)
Find_Package (GLUT)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

# File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set (OGLTargets)
Include_Directories (${GLUT_INCLUDE_DIR})

# ForEach (file ${SOURCES})
# 	Get_FileName_Component (exeName ${file} NAME_WE)
#   String (CONFIGURE ${dir_tmpl} dir @ONLY)

#   File (GLOB CPP_FILES ${dir}/*.cpp)
#   File (GLOB H_FILES ${dir}/*.h)
#   File (GLOB HPP_FILES ${dir}/*.hpp)

#   Set (exeName ogl-${exeName})

#   Include_Directories (${dir})
#   Add_Executable(${exeName} ${file})

#   Target_Link_Libraries (
#     ${exeName} ${GLUT_glut_LIBRARY} ${OPENGL_LIB}
#     )

#   List (APPEND OGLTargets ${exeName})
#   Get_Filename_Component (GLUT_BIN_DIR ${GLUT_INCLUDE_DIR} PATH)
#   Set (GLUT_BIN_DIR ${GLUT_BIN_DIR}/bin)

#   IF (UNIX)
#     Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
#   Else (UNIX)
#     Create_Vcxproj_User_File (${exeName} --lib-dir ${GLUT_BIN_DIR})
#     Set_Property (TARGET ${exeName} PROPERTY FOLDER "OpenGL Samples")
#   EndIf (UNIX)

# EndForEach (file ${SOURCES})

File (GLOB all_files "*")
ForEach (f ${all_files})
  If (IS_DIRECTORY ${f})
    get_filename_component (lib ${f} NAME)
    string (COMPARE NOTEQUAL "${lib}" "lib" consider)
    If (${consider})
      Add_Subdirectory (${f})
    EndIf()
  EndIf()
EndForEach()

If (UNIX)
  Add_Custom_Target (ogl DEPENDS ${OGLTargets}) 
EndIf (UNIX)
