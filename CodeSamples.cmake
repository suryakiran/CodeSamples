Macro (CODESAMPLES_VCXPROJ_USER_FILE exeName)
  If (NOT UNIX)
    Create_Vcxproj_User_File (
      ${exeName}
      -a srcdir=${CMAKE_SOURCE_DIR}
      -a cur_srcdir=${CMAKE_CURRENT_SOURCE_DIR}
      -a bindir=${CMAKE_BINARY_DIR}
      -a cur_bindir=${CMAKE_CURRENT_BINARY_DIR}
      ${ARGN}
      )
  EndIf (NOT UNIX)
EndMacro (CODESAMPLES_VCXPROJ_USER_FILE)

Macro (CODESAMPLES_CREATE_WRAPPER exeName)
  If (UNIX)
    Configure_Executable_File (${PERL_IN_FILE} ${CMAKE_BINARY_DIR}/${exeName} @ONLY)
  Else (UNIX)
    CodeSamples_Vcxproj_User_File (${exeName})
  EndIf (UNIX)
EndMacro (CODESAMPLES_CREATE_WRAPPER exeName)

Macro (CODESAMPLES_DIRECTORY_TARGET)
  If (UNIX)
    Add_Custom_Target (${ARGN})
  EndIf (UNIX)
EndMacro (CODESAMPLES_DIRECTORY_TARGET)
