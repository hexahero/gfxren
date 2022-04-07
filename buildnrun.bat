echo d | xcopy /s /y /d 3d_gfx_renderer\shaders bin\shaders
msbuild gfxren.sln /p:configuration=release /p:platform=x64
cd bin
start "" "gfxren.exe"
