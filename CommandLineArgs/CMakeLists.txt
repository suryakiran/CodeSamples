Project (CommandLineArgs)

File (GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)
File (GLOB HXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hxx)

Add_Library (
  ${ParseArgsLib} SHARED ${CXX_FILES} ${HXX_FILES}
  )

Target_Link_Libraries (
  ${ParseArgsLib}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  )
