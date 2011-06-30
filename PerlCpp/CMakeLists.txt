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

Set (PERL_XSI_FILE ${CMAKE_CURRENT_BINARY_DIR}/perlxsi.c)
Add_Custom_Command (
  OUTPUT ${PERL_XSI_FILE}
  COMMAND ${PERL_EXECUTABLE} -MExtUtils::Embed -e xsinit -- -o ${PERL_XSI_FILE} Test
  )

Include_Directories (
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${PERL_INCLUDE_PATH}
  )

File (GLOB CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)
File (GLOB HXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hxx)
Add_Executable (PerlTest ${CXX_FILES} ${HXX_FILES} ${PERL_XSI_FILE})
Target_Link_Libraries (
  PerlTest
  ${PerlCppSrcLib}
  ${PerlCppSrcExtnLib}
  ${PERL_LIBRARY}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  )

File (GLOB IN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/perl/*.in)

ForEach (inf ${IN_FILES})
  Get_Filename_Component (InFile ${CMAKE_CURRENT_SOURCE_DIR}/perl/${inf} NAME_WE)
  Configure_File (
    ${inf}
    ${CMAKE_CURRENT_BINARY_DIR}/${InFile}
    @ONLY
    )

  File (
    COPY ${CMAKE_CURRENT_BINARY_DIR}/${InFile} DESTINATION ${CMAKE_BINARY_DIR}
    FILE_PERMISSIONS 
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
    )
EndForEach (inf)

