Project(TabFocus)

Set (exeName tab_focus)

Get_Filename_Component (ui_dir ${CMAKE_CURRENT_SOURCE_DIR}/../Ui ABSOLUTE)
Get_Filename_Component (inc_dir ${CMAKE_CURRENT_SOURCE_DIR}/../Include ABSOLUTE)

Set_Property (
  DIRECTORY APPEND
  PROPERTY INCLUDE_DIRECTORIES ${inc_dir}
  )

Set (mainFile ${CMAKE_CURRENT_BINARY_DIR}/${exeName}_main.cxx)

Execute_Python (
  FILE ${PY_COMMANDS_FILE}
  ARGS -c to_camel_case ${exeName}_window
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

Configure_Executable_File (
  ${PYTHON_IN_FILE}
  ${CMAKE_BINARY_DIR}/${exeName}
  @ONLY
  )

Set_Property (
  DIRECTORY ${QtSamplesDir} APPEND
  PROPERTY QtTargets ${exeName}
  )

