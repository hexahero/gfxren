@echo off

msbuild gfxren.sln /p:configuration=release /p:platform=x64
echo:
echo [7m [7mNOTE: In case of failure make sure that MSBuild environment variable is set[0m
echo:

pause