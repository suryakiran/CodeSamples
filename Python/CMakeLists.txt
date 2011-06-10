Project(Python)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exe_name@_files)

File (GLOB CXX_FILES *.cxx)
File (GLOB COMMON_FILES *.h)

Include_Directories (${PYTHON_INCLUDE_DIRS})

ForEach (cf ${CXX_FILES})
  Get_Filename_Component (exe_name ${cf} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)
  Include_Directories (${dir})
  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  Add_Executable (${exe_name} ${cf} ${CPP_FILES} ${H_FILES} ${COMMON_FILES})
  Target_Link_Libraries (${exe_name} ${PYTHON_LIBRARIES})
EndForEach (cf)
