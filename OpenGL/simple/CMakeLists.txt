Project(openglSimple)

Set (exeName "ogl-simple")

File (GLOB cxx_files "*.cxx")
File (GLOB hxx_files "*.hxx")
qt5_wrap_cpp (moc_files ${hxx_files})

Add_Executable (${exeName} ${cxx_files} ${moc_files} ${hxx_files})

Target_Link_Libraries (${exeName} ${OPENGL_LIB})

Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)

List (APPEND OGLTargets ${exeName})
