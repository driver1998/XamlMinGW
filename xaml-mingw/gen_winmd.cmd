@echo off
setlocal enabledelayedexpansion

set VSWHERE="%PROGRAMFILES(X86)%\Microsoft Visual Studio\Installer\vswhere.exe"
for /f "usebackq tokens=*" %%i in (`%VSWHERE% -latest -find VC\Auxiliary\Build\vcvars32.bat`) do (
  set VCVARS=%%i
)

call "%VCVARS%"

midl -winrt -nomidl -h nul -metadata_dir "%CD%\references" -reference "%CD%\references\Windows.winmd" %1 -winmd %~n1.winmd
