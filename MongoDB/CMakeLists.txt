Project(MongoDB)

Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set (MongoDBTargets)
Find_Package(MongoDB)
Find_Package(Threads)
Include_Directories (${MONGODB_INCLUDE_DIR})

ForEach (file ${SOURCES})
  Get_FileName_Component (exeName ${file} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)

  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  File (GLOB HPP_FILES ${dir}/*.hpp)

  Set (ProjectName "MongoDB Tests ${exeName}")
  Set (exeName mongo-${exeName})

  Include_Directories (${dir})
  Add_Executable(${exeName} ${file} ${CPP_FILES} ${H_FILES} ${HPP_FILES})

  Set_Target_Properties (
    ${exeName} PROPERTIES 
    PROJECT_LABEL ${ProjectName}
    )

  Target_Link_Libraries (${exeName} 
    ${Boost_PROGRAM_OPTIONS_LIBRARIES}
    ${Boost_REGEX_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARIES}
    ${Boost_SYSTEM_LIBRARIES}
    ${Boost_THREAD_LIBRARIES}
    ${MONGODB_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    )

  List (APPEND MongoDBTargets ${exeName})
  Get_Target_Property (CURRENT_EXE_FILE ${exeName} LOCATION)
  Configure_Executable_File (${PYTHON_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)

EndForEach (file ${SOURCES})

Add_Custom_Target (mongodb DEPENDS ${MongoDBTargets}) 
