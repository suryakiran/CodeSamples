Project(OSG)

Find_Package (OpenSceneGraph 3.0.1 REQUIRED osgDB osgUtil osgViewer osgGA)
If (OPENSCENEGRAPH_FOUND)
  Find_Program (OSGVIEWER_EXE osgviewer)
EndIf (OPENSCENEGRAPH_FOUND)
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

  Include_Directories (${dir} ${OSG_INCLUDE_DIR})
  Target_Link_Libraries (${exeName} ${OPENSCENEGRAPH_LIBRARIES})

  List (APPEND OSGTargets ${exeName})
  If (UNIX)
    Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
  Else(UNIX)
    Get_Filename_Component (OSG_BIN_PATH ${OSGVIEWER_EXE} PATH)
    Create_Vcxproj_User_File (${exeName} --lib-dir ${OSG_BIN_PATH})
  EndIf (UNIX)

EndForEach (file ${SOURCES})

Add_Custom_Target (osg DEPENDS ${OSGTargets}) 
