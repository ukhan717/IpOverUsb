:;# Script can run under Windows CMD and Linux bash
:<<"END_CMD"
: CMD script start -----------------------------------------------
@Echo Off
Setlocal enabledelayedexpansion
reg query HKCU\Software\SEGGER\J-Link /v InstallPath
IF ERRORLEVEL 1 goto ERR
for /f "tokens=3,*" %%b in ('reg query "HKCU\Software\SEGGER\J-Link" /v InstallPath  ^|findstr /ri "REG_SZ"') do set _JLINKEXE="%%b %%cjlink.exe"
!_JLINKEXE! -device STM32F746NG -CommanderScript CommandFile.jlink
pause
: CMD script end -------------------------------------------------
@EXIT /B
END_CMD
(tr -d '\r' | bash) <<"END_BASH"
# bash script start ----------------------------------------------
set -e
if [[ "$OSTYPE" == "linux-gnu" ]]; then
  JLINK_SEARCH_PATH=/opt/SEGGER/JLink/
elif [[ "$OSTYPE" == "darwin"* ]]; then
   JLINK_SEARCH_PATH=/Applications/SEGGER/JLink/
else
  echo "Unknown OS, exiting"
  exit 1
fi

if [ "x$JLINK_SEARCH_PATH" = "x" ]; then
    echo "J-Link package not found, please install from https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack !"
    exit 1
fi
JLINKEXE=$( find  $JLINK_SEARCH_PATH -name JLinkExe 2> /dev/null| sort | tail -n 1 )
$JLINKEXE -device STM32F746NG -CommanderScript CommandFile.jlink
# bash script end ------------------------------------------------
END_BASH




