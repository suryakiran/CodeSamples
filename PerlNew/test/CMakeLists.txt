Project (Test)

Create_Ppport_File()
Create_Stl_Map_File()

Set (PARSE_XS_PL_FILE ${CMAKE_MODULE_PATH}/ParseXs.pl)
Include_Directories (
  ${CMAKE_CURRENT_SOURCE_DIR} 
  ${PERL_INCLUDE_PATH} 
  ${CMAKE_CURRENT_BINARY_DIR}
  )

Add_Library (${Example_Lib} SHARED 
  ${CMAKE_CURRENT_SOURCE_DIR}/Example.cpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/Example.h
  )

Get_Filename_Component (XsDir ${CMAKE_CURRENT_SOURCE_DIR}/../xs ABSOLUTE)
File (GLOB XS_FILES ${XsDir}/*.xs)

Set (XS_CPP_FILES)

ForEach (xsf ${XS_FILES})
  Get_Filename_Component (xs_name ${xsf} NAME_WE)
  Set (CPP_FILE ${CMAKE_CURRENT_BINARY_DIR}/${xs_name}.cpp)
  List (APPEND XS_CPP_FILES ${CPP_FILE})
  Add_Custom_Command (
    OUTPUT 
      ${CPP_FILE}
    COMMAND
      ${PERL_EXECUTABLE} ${PARSE_XS_PL_FILE} -xs ${xsf} -o ${CPP_FILE} 
      -t ${XsDir}/typemap -t ${XsDir}/perlobject.map -t ${CMAKE_CURRENT_BINARY_DIR}/stl.typemap
    DEPENDS 
    ${xsf} ${PARSE_XS_PL_FILE} ${XsDir}/typemap
  )
EndForEach (xsf)

Add_Custom_Target (xs DEPENDS ${XS_CPP_FILES})

Add_Library (
    Example SHARED
  ${XS_CPP_FILES}
  )

Set_Source_Files_Properties (
  ${XS_CPP_FILES}
  PROPERTIES GENERATED TRUE
  )

Target_Link_Libraries (
    Example ${PERL_LIBRARY} ${Example_Lib}
  )
