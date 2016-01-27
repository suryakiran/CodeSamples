Project(OpenGLLib)

Set (OPENGL_LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

If (NOT Qt5OpenGL_FOUND)
  Find_Package(Qt5OpenGL)
EndIf()

Find_Package (OpenGL)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
File (GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

qt5_wrap_cpp(lib_moc_files ${HEADERS})

Add_Library (${OPENGL_LIB} SHARED ${SOURCES} ${lib_moc_files})

Target_Link_Libraries (${OPENGL_LIB} Qt5::Widgets Qt5::OpenGL ${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY}) 
Add_Custom_Target (gl DEPENDS ${OPENGL_LIB})

