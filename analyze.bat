@echo off

cppcheck --project=gfxren.cppcheck --enable=all --suppress=unusedFunction
echo:
echo [7m [7mNOTE: In case of failure make sure that cppcheck environment variable is set[0m
echo:

pause