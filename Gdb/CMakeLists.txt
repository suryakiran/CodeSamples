Project(Gdb)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set (GdbTargets)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)

  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  File (GLOB HPP_FILES ${dir}/*.hpp)

  Set (ProjectName "Gdb Tests ${exeName}")
  Set (exeName gdb-${exeName})

  Include_Directories (${dir})
  Add_Executable(${exeName} ${file} ${Gdb_FILES} ${H_FILES} ${HPP_FILES})

	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)

            Target_Link_Libraries (
                ${exeName}
                ${QT_LIBRARIES}
                )

  List (APPEND GdbTargets ${exeName})
  Set(qt_lib_dirs)
  ForEach (lib ${QT_LIBRARIES})
      Get_Filename_Component(dir ${lib} PATH)
      If (qt_lib_dirs)
          Set (qt_lib_dirs "${qt_lib_dirs},\n'${dir}'")
      Else(qt_lib_dirs)
          Set (qt_lib_dirs "'${dir}'")
      EndIf(qt_lib_dirs)
  EndForEach(lib)
  Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)

EndForEach (file ${SOURCES})

Add_Custom_Target (gdb DEPENDS ${GdbTargets}) 
