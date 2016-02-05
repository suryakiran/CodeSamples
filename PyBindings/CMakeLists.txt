Project(Python)

Set (CMAKE_SKIP_BUILD_RPATH FALSE)
Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exe_name@_files)

File (GLOB CXX_FILES *.cxx)
File (GLOB COMMON_FILES *.h)

Include_Directories (${PYTHON_INCLUDE_DIRS})
Set (PythonTargets)

ForEach (cf ${CXX_FILES})
  Get_Filename_Component (libName ${cf} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)
  Include_Directories (${dir})
  Add_Library (${libName} SHARED ${cf} ${COMMON_FILES})
  Add_Library (mod${libName} SHARED ${CMAKE_CURRENT_SOURCE_DIR}/mod${libName}.cpp)
  List (APPEND PythonTargets ${libName})
  List (APPEND PythonTargets mod${libName})
  set_target_properties(mod${libName} PROPERTIES PREFIX "" )
  Target_Link_Libraries (${libName} ${PYTHON_LIBRARIES} ${Boost_PYTHON_LIBRARY})
  Target_Link_Libraries (mod${libName} ${PYTHON_LIBRARIES} ${Boost_PYTHON_LIBRARY} ${libName})
EndForEach (cf)

Add_Custom_Target(python DEPENDS ${PythonTargets})
