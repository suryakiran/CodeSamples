Project(Dumper)
Set(exe_file main)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Include_Directories (${GenericDir}/Include)
Find_Package(PkgConfig REQUIRED)
pkg_check_modules(Json REQUIRED jsoncpp) 
pkg_check_modules(Yaml REQUIRED yaml-cpp)

Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
Include_Directories (${Json_INCLUDE_DIRS} ${Yaml_INCLUDE_DIRS} ${Qt5Core_DIR})

Add_Executable(
  ${exe_file}
  ${SOURCES}
  )

Target_Link_Libraries (
  ${exe_file}
  ${Json_LIBRARIES}
  ${Yaml_LIBRARIES}
  Qt5::Core
  )
