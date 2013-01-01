Project(QtMain)

Get_Filename_Component (ui_dir ${CMAKE_CURRENT_SOURCE_DIR}/../Ui ABSOLUTE)

Qt_Library (
  NAME ${QT_MAIN_LIB}
  UI_DIR ${ui_dir}
  )

Get_Property (
  id 
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  PROPERTY INCLUDE_DIRECTORIES)

ForEach (d ${id})
  Set_Property (
    GLOBAL APPEND
    PROPERTY main_include_dirs ${d})
EndForEach(d)

