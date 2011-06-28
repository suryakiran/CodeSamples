Project (PerlCppSrc)

File (GLOB CPP_FILES *.cpp)
File (GLOB H_FILES *.h)

Set (LibName ${PerlCppSrcLib})
Set (LIBNAME ${LibName})
Configure_File (${CMAKE_DLL_H_IN_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${LibName}.hxx)
Add_Library (${PerlCppSrcLib} SHARED ${CPP_FILES} ${H_FILES})
