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
