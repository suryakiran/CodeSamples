Project(MT)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set (MTTargets)
Find_Package (Threads)

IF (UNIX)
  Find_Package (Motif)
  Find_Package (X11)
EndIf (UNIX)

If (USE_GTKMM)
  Pkg_Check_Modules (GTKMM gtkmm-3.0)
  Include_Directories (${GTKMM_INCLUDE_DIRS})
EndIf (USE_GTKMM)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)

  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  File (GLOB HPP_FILES ${dir}/*.hpp)

  Set (ProjectName "MT Tests ${exeName}")
  Set (exeName mt-${exeName})

  Include_Directories (${dir})
  Add_Executable(${exeName} ${file} ${CPP_FILES} ${H_FILES} ${HPP_FILES})

	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)

  Target_Link_Libraries (
    ${exeName} ${CMAKE_THREAD_LIBS_INIT} ${Boost_THREAD_LIBRARY}
    ${Boost_SIGNALS_LIBRARY}
    ${MOTIF_LIBRARIES} ${X11_X11_LIB} ${GTKMM_LIBRARIES}
    )

  List (APPEND MTTargets ${exeName})
  Get_Target_Property (CURRENT_EXE_FILE ${exeName} LOCATION)
  Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)

EndForEach (file ${SOURCES})

Add_Custom_Target (mt DEPENDS ${MTTargets}) 
