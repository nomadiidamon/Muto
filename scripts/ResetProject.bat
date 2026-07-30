@echo off

REM This script resets the project by removing generated files and directories.

setlocal

set SCRIPT_DIR=%~dp0
pushd "%SCRIPT_DIR%\.."

echo.
echo ==========================================
echo Resetting Project
echo ==========================================
echo.

if exist "bin" (
    echo Removing Binaries...
    rmdir /S /Q "bin"
)

if exist "bin-int" (
    echo Removing Intermediate...
    rmdir /S /Q "bin-int"
)

for %%F in (*.sln) do (
    echo Removing %%F...
    del /Q "%%F"
)

echo.
echo Project reset complete.

popd
if "%~1" NEQ "nopause" pause
