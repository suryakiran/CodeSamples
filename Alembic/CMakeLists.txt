Project(Alembic)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

# Include_Directories (${GenericDir}/Include)
# Find_Package(HDF5 REQUIRED)
Find_Package(Alembic)
Find_Package(PkgConfig REQUIRED)
# pkg_check_modules(Yaml REQUIRED yaml-cpp)
pkg_check_modules(Ilm REQUIRED OpenEXR)

Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
Include_Directories (${Yaml_INCLUDE_DIRS} ${ALEMBIC_INCLUDE_DIR} ${Ilm_INCLUDE_DIRS})

message (${CMAKE_CXX_FLAGS})
ForEach (file ${SOURCES})
  Get_FileName_Component (exeName ${file} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)
  Set (ProjectName "Alembic Tests ${exeName}")
  Set (exeName alm-${exeName})
  Add_Executable(${exeName} ${file})
  # Set_Target_Properties (
  #   ${exeName} PROPERTIES 
  #   PROJECT_LABEL ${ProjectName}
  #   COMPILE_FLAGS -I${dir}
  #   )

  Target_Link_Libraries (
    ${exeName}
    # ${Yaml_LIBRARIES}
    Half Iex
    ${ALEMBIC_LIBRARIES}
    )

  List (APPEND ALEMBICTargets ${exeName})
  # Get_Target_Property (CURRENT_EXE_FILE ${exeName} LOCATION)
  # Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)

EndForEach (file ${SOURCES})

Add_Custom_Target (alm DEPENDS ${ALEMBICTargets})

