Project (PerlCppSrc)

File (GLOB CPP_FILES *.cpp)
File (GLOB H_FILES *.h)

Add_Library (${PerlCppSrcLib} SHARED ${CPP_FILES} ${H_FILES})
