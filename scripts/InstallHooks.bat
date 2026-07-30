@echo off
setlocal EnableDelayedExpansion

set SCRIPT_DIR=%~dp0
pushd "%SCRIPT_DIR%\.."

echo Installing Git hooks...
echo.
echo.

if not exist ".git" (
    echo ERROR: This is not a Git repository.
    popd
    pause
    exit /b 1
)

set HOOKS=pre-commit
set INSTALL_FAILED=0

for %%H in (%HOOKS%) do (

	set SOURCE_FILE=scripts\hooks\%%H
	set DEST_FILE=.git\hooks\%%H

    if exist "!DEST_FILE!" (
        echo Updating %%H...
    ) else (
        echo Installing %%H...
    )

    copy /Y "!SOURCE_FILE!" "!DEST_FILE!" >nul
	
	if errorlevel 1 (
		echo [FAILED] Could not copy %%H.
		set INSTALL_FAILED=1
	) else (
		echo [OK] Copied %%H.
	)
	
)

if "%INSTALL_FAILED%"=="0" (
    echo Git hooks are installed.
) else (
    echo ERROR: One or more Git hooks failed to install.
)

echo.
echo.

popd
if "%1" NEQ "nopause" pause