Project(openglSimple)

Set (exeName "ogl-simple")

File (GLOB cxx_files "*.cxx")
File (GLOB hxx_files "*.hxx")
qt5_wrap_cpp (moc_files ${hxx_files})

Add_Executable (${exeName} ${cxx_files} ${moc_files} ${hxx_files})

Target_Link_Libraries (${exeName} ${OPENGL_LIB})

List (APPEND OGLTargets ${exeName})
