Project (CommandLineArgs)

File (GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)
File (GLOB HXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hxx)

Set (LibName ${ParseArgsLib})
Set (DLL_H_OUT_FILE ${DLL_UTILITIES_DIR}/DLLParseArgs.hxx)
Configure_File (${CMAKE_DLL_H_IN_FILE} ${DLL_H_OUT_FILE})
Add_Library (
  ${ParseArgsLib} SHARED ${CXX_FILES} ${HXX_FILES} ${DLL_H_OUT_FILE}
  )

Target_Link_Libraries (
  ${ParseArgsLib}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  )
