Project (DownloadFileGui)

Find_Package (Qt4)
Include (${QT_USE_FILE})
Include (${CMAKE_MODULE_PATH}/Qt.cmake)
Include_Directories (${CMAKE_CURRENT_BINARY_DIR})
Add_Definitions ("-DQT_NO_KEYWORDS")

Qt_Exe (
	NAME DownloadFileGui
	UI_DIR UiFiles
	RC_DIR Resources
	)
