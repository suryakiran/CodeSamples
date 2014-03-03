Project(QAction)

Set (exeName qaction)

Get_Filename_Component (ui_dir ${CMAKE_CURRENT_SOURCE_DIR}/../Ui ABSOLUTE)
Get_Filename_Component (inc_dir ${CMAKE_CURRENT_SOURCE_DIR}/../Include ABSOLUTE)

Set_Property (
  DIRECTORY APPEND
  PROPERTY INCLUDE_DIRECTORIES ${inc_dir}
  )

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
  ${main_cxx_in_file}
  ${mainFile}
  @ONLY
  )

Set (exeName qt-${exeName})
Qt_Exe (
  NAME ${exeName}
  UI_DIR ${ui_dir}
  OTHER_SOURCES ${mainFile}
  )

Target_Link_Libraries (
  ${exeName}
  ${QT_MAIN_LIB}
  )

Process_Perl_Template (
  PERL_FILE ${PL_FILE_SAMPLES_EXE}
  TEMPLATE ${CMAKE_SAMPLES_TMPL}
  OUTPUT ${CMAKE_BINARY_DIR}/${exeName}
  ARGS -e ${exeName} -d ${QT_MAIN_LIB_DIR}
  )

Set_Property (
  DIRECTORY ${QtSamplesDir} APPEND
  PROPERTY QtTargets ${exeName}
  )

