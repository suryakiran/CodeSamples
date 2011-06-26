Project (PerlNew)

Set (Example_Lib ExampleLib)
Add_Subdirectory (test)

Include_Directories (${CMAKE_CURRENT_SOURCE_DIR})

Add_Executable (
  perl-test
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  )

Target_Link_Libraries (
  perl-test
  ${Example_Lib}
  )
