Project(Qt)

Find_Package (Qt5Widgets)
Set (CMAKE_AUTOMOC ON)
# Include (${QT_USE_FILE})
# Include_Directories (main ${CMAKE_CURRENT_BINARY_DIR}/main)

# Set (QT_MAIN_LIB SamplesQt)
# Set (QtSamplesDir ${CMAKE_CURRENT_SOURCE_DIR})

# Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File(GLOB all_files "*")
Include_Directories(${Qt5Widgets_INCLUDE_DIRS})

# Set(dirs)
# Set(main_include_dirs)
# Set(main_cxx_in_file ${CMAKE_CURRENT_SOURCE_DIR}/main.cxx.in)

ForEach (f ${all_files})
  If(IS_DIRECTORY ${f})
    Add_Subdirectory(${f}/Src)
  #   Get_Filename_Componentl(dir ${f} NAME)
  #   If(${dir} STREQUAL "main")
  #     Include_Directories(${CMAKE_CURRENT_SOURCE_DIR}/${dir}/Include)
  #     Add_Subdirectory(${dir})
  #   Else()
  #     List(APPEND dirs ${dir})
  #   EndIf()
  EndIf()
EndForEach(f)

# Get_Target_Property (
#   QT_MAIN_LIB_DIR ${QT_MAIN_LIB} LOCATION
#   )

# Get_Property(main_include_dirs GLOBAL PROPERTY main_include_dirs)

# ForEach (d ${main_include_dirs})
#   Include_Directories(${d})
# EndForEach(d)

# ForEach(d ${dirs})
#   Add_Subdirectory(${d})
# EndForEach(d)

# Get_Property (QtTargets DIRECTORY PROPERTY QtTargets)
# Add_Custom_Target (qt DEPENDS ${QtTargets}) 
