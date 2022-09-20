@echo off

echo --------------------------------------
echo [93m [93m Moving shaders [0m
echo d | XCOPY "src\shaders\" "bin\shaders\" /S /Y /D

echo [93m [93m Moving dependencies [0m
echo d | XCOPY "dependencies\assimp\lib\assimp-vc143-mt.dll" "bin\" /S /Y /D
echo --------------------------------------

echo [42m                 Done                 [0m
pause