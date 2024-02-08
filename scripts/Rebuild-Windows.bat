@echo off

pushd ..
for /r . /d %%a in (*) do if /i "%%~nxa"=="bin" del /s /q %%a & rmdir /s /q %%a
for /r . /d %%a in (*) do if /i "%%~nxa"=="bin-int" del /s /q %%a & rmdir /s /q %%a
del /s *.sln
del /s *.vcxproj*
vendor\premake-5.0.0-beta2-windows\premake5.exe --file=premake5.lua vs2022
popd
pause