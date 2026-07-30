@echo off
setlocal

echo Running encoding fix...

call "%~dp0CheckEncoding.bat" fix

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Encoding fix failed.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo Encoding fix complete.
if "%~1" NEQ "nopause" pause