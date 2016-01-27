Project(main)

Set (CMAKE_INCLUDE_CURRENT_DIR ON)

Get_Filename_Component (ui_dir ${CMAKE_CURRENT_SOURCE_DIR}/../Ui ABSOLUTE)
File(GLOB main_ui_files "${ui_dir}/*")
File(GLOB main_src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx")
File(GLOB main_header_files "${CMAKE_CURRENT_SOURCE_DIR}/../Include/*.hxx")

qt5_wrap_cpp(main_moc_files ${main_header_files})
qt5_wrap_ui(main_ui_cpp_files ${main_ui_files})
Include_Directories (${CMAKE_CURRENT_SOURCE_DIR}/../Include)

add_executable(main ${main_src_files} ${main_moc_files} ${main_ui_cpp_files} ${CMAKE_CURRENT_SOURCE_DIR}/../main.cxx)
target_link_libraries (main Qt5::Widgets)


# Qt_Library (
#   NAME ${QT_MAIN_LIB}
#   UI_DIR ${ui_dir}
#   )

# Get_Property (
#   id 
#   DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#   PROPERTY INCLUDE_DIRECTORIES)

# ForEach (d ${id})
#   Set_Property (
#     GLOBAL APPEND
#     PROPERTY main_include_dirs ${d})
# EndForEach(d)

