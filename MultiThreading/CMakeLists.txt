Project(MT)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)
Set (QT_SAMPLES qt)
Set (GTKMM_SAMPLES gtkmm)

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

If (USE_QT)
  Include_Directories (
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_QTGUI_INCLUDE_DIR}
    )
EndIf (USE_QT)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
  Set (is_qt_sample)
  List (FIND QT_SAMPLES ${exeName} is_qt_sample)
  List (FIND GTKMM_SAMPLES ${exeName} is_gtkmm_sample)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)

  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  File (GLOB HPP_FILES ${dir}/*.hpp)

  If (NOT "${is_qt_sample}" STREQUAL -1)
    File (GLOB UI_FILES ${dir}/*.ui)
    If (UI_FILES)
      Qt4_Wrap_Ui (UI_SRCS ${UI_FILES})
      List (APPEND OTHER_SOURCES ${UI_FILES})
      Include_Directories (${CMAKE_CURRENT_BINARY_DIR})
    EndIf (UI_FILES)
    Qt_Get_Moc_Files (MOC_SRCS ${HPP_FILES})
    List (APPEND OTHER_SOURCES ${MOC_SRCS})
  EndIf (NOT "${is_qt_sample}" STREQUAL -1)

  Set (ProjectName "MT Tests ${exeName}")
  Set (exeName mt-${exeName})

  Include_Directories (${dir})

  Add_Executable(
    ${exeName} ${file} ${CPP_FILES} ${H_FILES} ${HPP_FILES}
    ${OTHER_SOURCES}
  )

	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
		)

  Target_Link_Libraries (
    ${exeName} ${CMAKE_THREAD_LIBS_INIT} ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY} ${Boost_DATE_TIME_LIBRARY} ${Boost_REGEX_LIBRARY}
    ${MOTIF_LIBRARIES} ${X11_X11_LIB} ${GTKMM_LIBRARIES}
    ${QT_QTCORE_LIBRARIES}
    ${QT_QTGUI_LIBRARIES}
    )

  Get_Filename_Component (ZORBA_BIN_PATH ${ZORBA_EXECUTABLE} PATH CACHE)

  List (APPEND MTTargets ${exeName})

  If (UNIX)
    Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
  Else (UNIX)
    Execute_Perl (
      FILE 
        ${PL_FILE_VCXPROJ_USER_FILE}
      ARGS 
        -o ${CMAKE_CURRENT_BINARY_DIR}/${exeName}.vcxproj.user
        -x ${CMAKE_VARIABLES_XML_OUT_FILE}
        -e ${exeName}
      )
  EndIf (UNIX)

EndForEach (file ${SOURCES})

Add_Custom_Target (mt DEPENDS ${MTTargets}) 
