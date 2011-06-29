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
Target_Link_Libraries (PerlTest ${PerlCppSrcLib} ${PerlCppSrcExtnLib}
  ${PERL_LIBRARY})
