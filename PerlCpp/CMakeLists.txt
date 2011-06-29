Project (PerlCpp)

Set (PerlCppSrcLib "PerlCppSrc")
Set (PerlCppSrcExtnLib "Test")

Include_Directories (
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_BINARY_DIR}/src
  )

Add_Subdirectory (src)

Set (${CMAKE_PERL_DIR} ${CMAKE_MODULE_PATH}/perl)
Add_Subdirectory (xs)

Include_Directories (
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${PERL_INCLUDE_PATH}
  )
File (GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)
File (GLOB HXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hxx)
Add_Executable (PerlTest ${CXX_FILES} ${HXX_FILES})
Target_Link_Libraries (
  PerlTest
  ${PerlCppSrcLib}
  ${PerlCppSrcExtnLib}
  ${PERL_LIBRARY}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  )

Configure_File (
  ${CMAKE_CURRENT_SOURCE_DIR}/perl/perl-test.pl.in
  ${CMAKE_CURRENT_BINARY_DIR}/perl-test.pl 
  @ONLY
  )

File (
  COPY ${CMAKE_CURRENT_BINARY_DIR}/perl-test.pl DESTINATION ${CMAKE_BINARY_DIR}
  FILE_PERMISSIONS 
  OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )
