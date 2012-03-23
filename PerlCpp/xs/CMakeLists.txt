Project(PerlCppXs)

Create_Ppport_File()
Create_Stl_Map_File()

Set (PARSE_XS_PL_FILE ${CMAKE_PERL_DIR}/ParseXS.pl)
File (GLOB XS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.xs)

Include_Directories (
  ${CMAKE_CURRENT_BINARY_DIR}
  ${PERL_INCLUDE_PATH}
  )

Set (XS_CPP_FILES)

ForEach (xsf ${XS_FILES})
  Get_Filename_Component (xs_name ${xsf} NAME_WE)
  Set (CPP_FILE ${CMAKE_CURRENT_BINARY_DIR}/${xs_name}.cpp)
  List (APPEND XS_CPP_FILES ${CPP_FILE})
  Execute_Process (
    COMMAND 
    ${PERL_EXECUTABLE} ${CMAKE_PERL_DIR}/GetXSDependencies.pl -f ${xsf} -s ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE
      DepsOut
    ERROR_VARIABLE 
      DepsError
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
    )

  Add_Custom_Command (
    OUTPUT 
      ${CPP_FILE}
    COMMAND
      ${PERL_EXECUTABLE} ${PARSE_XS_PL_FILE} -xs ${xsf} -o ${CPP_FILE} 
      --source-dir=${CMAKE_CURRENT_SOURCE_DIR}
      --binary-dir=${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS 
      ${xsf} ${PARSE_XS_PL_FILE} ${DepsOut}
  )
EndForEach (xsf)

Add_Custom_Target (xs DEPENDS ${XS_CPP_FILES})
Set_Property (TARGET xs PROPERTY FOLDER "Perl CPP Samples")

Set (LibName ${PerlCppSrcExtnLib})
Set (LIBNAME ${LibName})
Include_Directories (${CMAKE_CURRENT_BINARY_DIR})
Configure_File (${CMAKE_DLL_H_IN_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${LibName}.hxx)

Add_Library (
  ${PerlCppSrcExtnLib}
  SHARED ${XS_CPP_FILES}
  )

Target_Link_Libraries (
  ${PerlCppSrcExtnLib} ${PERL_LIBRARY} ${PerlCppSrcLib}
  )
Set_Property (TARGET ${PerlCppSrcExtnLib} PROPERTY FOLDER "Perl CPP Samples")
