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
  If (UNIX)
    Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
  Else(UNIX)
    Get_Filename_Component (OSG_BIN_PATH ${OSGVIEWER_EXE} PATH)
    Execute_Perl (
      FILE
        ${PL_FILE_VCXPROJ_USER_FILE}
      ARGS
        -o ${CMAKE_CURRENT_BINARY_DIR}/${exeName}.vcxproj.user
        -e ${exeName}
        -x ${CMAKE_VARIABLES_XML_OUT_FILE}
        --lib-dir ${OSG_BIN_PATH}
        )
  EndIf (UNIX)

EndForEach (file ${SOURCES})

Add_Custom_Target (osg DEPENDS ${OSGTargets}) 
