@echo off
setlocal

set SCRIPT_DIR=%~dp0
pushd "%SCRIPT_DIR%\.."

set REPO_ROOT=%CD%
set TOOL_DIR=%REPO_ROOT%\tools
set VENV_DIR=%TOOL_DIR%\.venv
set PYTHON=%VENV_DIR%\Scripts\python.exe

echo Checking for Python...

python -m venv --help >nul 2>&1

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Python with the venv module was not found.
    echo.
    echo Install Python 3 from:
    echo.
    echo https://www.python.org/downloads/windows/
    echo.
    echo Make sure "Add python.exe to PATH" is selected.
    echo.
    pause
    popd
    exit /b 1
)

echo Python found.
echo.

echo Checking Python virtual environment...

if not exist "%PYTHON%" (
    echo Virtual environment not found. Creating...

    python -m venv "%VENV_DIR%"

    if not exist "%PYTHON%" (
        echo Failed to create virtual environment.
        pause
        popd
        exit /b 1
    )

    echo Installing dependencies...

    "%PYTHON%" -m pip install --upgrade pip
    "%PYTHON%" -m pip install -r "%TOOL_DIR%\requirements.txt"

    if %ERRORLEVEL% NEQ 0 (
        echo Failed to install dependencies.
        pause
        popd
        exit /b 1
    )
)

echo Virtual environment ready.
echo.

if "%1"=="fix" (
    echo Fixing file encodings...
    "%PYTHON%" "%TOOL_DIR%\fix_encoding.py" --fix
) else (
    echo Checking file encodings...
    "%PYTHON%" "%TOOL_DIR%\fix_encoding.py" --check
)

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Encoding check failed.
    pause
    popd
    exit /b %ERRORLEVEL%
)

echo.
echo Complete.

popd
if "%~1" NEQ "nopause" pause