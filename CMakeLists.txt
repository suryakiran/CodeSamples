Project (CodeSamples)

Cmake_Minimum_Required (VERSION 2.6)

If (UNIX)
	Add_Definitions ("-DUNIX")
	Set (CMAKE_SKIP_BUILD_RPATH TRUE)
Else (UNIX)
	Add_Definitions ("-DWINDOWS")
	Add_Definitions ("-DBOOST_TYPEOF_SILENT")
	Add_Definitions ("-DBOOST_ALL_DYN_LINK")
	If (${CMAKE_SYSTEM_VERSION} EQUAL 6.0)
		Add_Definitions ("-DWIN_VISTA")
	EndIf (${CMAKE_SYSTEM_VERSION} EQUAL 6.0)
EndIf (UNIX)

Set (GenericDir ${CMAKE_CURRENT_SOURCE_DIR}/../Generic)

Set (CMAKE_MODULE_PATH ${GenericDir}/CMake)
Include (${CMAKE_MODULE_PATH}/Macros.cmake)
Include (${CMAKE_MODULE_PATH}/Targets.cmake)
Include (${CMAKE_MODULE_PATH}/Compiler.cmake)

If (NOT CMAKE_BUILD_TYPE)
  Set (CMAKE_BUILD_TYPE "Debug")
EndIf (NOT CMAKE_BUILD_TYPE)

Add_Config_Flags (
	CONFIGURATION "Debug;RelWithDebInfo" 
	DEFINES "DEBUG"
	)

GET_BOOST ()

Find_Package (
  Boost ${BOOST_VERSION}
  COMPONENTS date_time program_options
  )

Include_Directories (${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
Link_Directories    (${Boost_LIBRARY_DIRS})

SET_GTK_FLAGS()

Add_Subdirectory (Multi-Index)
#Add_Subdirectory (Fusion)
Add_Subdirectory (FileReading)
Add_Subdirectory (Miscellaneous)
Add_Subdirectory (NG)
#Add_Subdirectory (PreProcessor)
Add_Subdirectory (Phoenix)
#Add_Subdirectory (Spirit)
#Add_Subdirectory (PropertyTree)
#Add_Subdirectory (Holidays)
#Add_Subdirectory (Templates)
#Add_Subdirectory (CPP)
Add_Subdirectory (DownloadFile)
