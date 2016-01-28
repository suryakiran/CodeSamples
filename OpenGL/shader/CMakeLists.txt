Project(openglShader)

Get_Filename_Component(exeName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
Set (exeName "ogl-${exeName}")

File (GLOB cxx_files "*.cxx")
File (GLOB hxx_files "*.hxx")
File (GLOB rc_files "*.qrc")

qt5_wrap_cpp (moc_files ${hxx_files})
qt5_add_resources (rc_out ${rc_files})

Add_Executable (${exeName} ${cxx_files} ${moc_files} ${hxx_files} ${rc_out})

Target_Link_Libraries (${exeName} ${OPENGL_LIB})

Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)

List (APPEND OGLTargets ${exeName})
