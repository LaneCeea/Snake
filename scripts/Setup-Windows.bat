@echo off
pushd ..
vendor\premake-5.0.0-beta2-windows\premake5.exe --file=premake5.lua vs2022
start Snake.sln
popd
pause