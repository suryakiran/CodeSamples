Project(Dumper)
Set(exe_file uuid-sample)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Include_Directories (${GenericDir}/Include)
Find_Package(PkgConfig REQUIRED)
pkg_check_modules(Yaml REQUIRED yaml-cpp)
pkg_check_modules(Uuid REQUIRED uuid)

Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
Include_Directories (${Uuid_INCLUDE_DIRS} ${Yaml_INCLUDE_DIRS})

Add_Executable(
  ${exe_file}
  ${SOURCES}
  )

Target_Link_Libraries (
  ${exe_file}
  ${Uuid_LIBRARIES}
  ${Yaml_LIBRARIES}
  )
