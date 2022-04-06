msbuild gfxren.sln /p:configuration=release /p:platform=x64
cd bin
start "" "gfxren.exe"