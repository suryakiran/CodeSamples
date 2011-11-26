Project(OSG)

Find_Package (OpenSceneGraph 3.0.1 REQUIRED osgDB osgUtil osgViewer)
Set (dir_tmpl ${CMAKE_CURRENT_SOURCE_DIR}/@exeName@_files)

File (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx)

Set (OSGTargets)

ForEach (file ${SOURCES})
	Get_FileName_Component (exeName ${file} NAME_WE)
  String (CONFIGURE ${dir_tmpl} dir @ONLY)
  File (GLOB CPP_FILES ${dir}/*.cpp)
  File (GLOB H_FILES ${dir}/*.h)
  Set (ProjectName "OSG Tests ${exeName}")
  Set (exeName osg-${exeName})
  Add_Executable(${exeName} ${file} ${CPP_FILES} ${H_FILES})
	Set_Target_Properties (
		${exeName} PROPERTIES 
		PROJECT_LABEL ${ProjectName}
    COMPILE_FLAGS -I${dir} -I${OPENSCENEGRAPH_INCLUDE_DIRS}
		)

  Target_Link_Libraries (
    ${exeName} ${OPENSCENEGRAPH_LIBRARIES}
    )

  List (APPEND OSGTargets ${exeName})
  Get_Target_Property (CURRENT_EXE_FILE ${exeName} LOCATION)
  Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)

EndForEach (file ${SOURCES})

Add_Custom_Target (osg DEPENDS ${OSGTargets}) 
