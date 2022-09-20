# **gfxren**
**Simplistic 3D graphics renderer implemented in C++ and OpenGL 3.3 API**<br>
Current project state: core functionality is implemented, awaiting further feature extension (in development)<br><br>
<img src='./meta/demo800px.gif'><br>

## **Build Requirements (tested)**<br>

- Windows 64-bit operating system
- Windows SDK 8.0 or newer
- Visual Studio Community 2015 or newer
- OpenGL 3.3 compatible video adapter

Build application with your Visual Studio IDE using soluton file `gfxren.sln`<br>
For an IDE agnostic build use `buildnrun.bat`, release only (`msbuild` path has to be set)<br>

## **Controls**<br>
`W, A, S, D` - Moves camera forwards, to the left, backwards and to the right respectively<br>
`Spacebar` - Moves camera upwards<br>
`M` - Toggle wireframe rendering mode (also changes camera mode)<br>
`T` - Toggle textureless rendering mode<br>
`I` - Print GPU info<br>
`Mouse scroll` - Zoom in/out

## **Features Implemented**<br>
- Keyboard and mouse input<br>
- Scene camera<br>
- Construction of primitive models (geometric shapes)<br>
- Support for model transformations in 3D space<br>
- Shader building and interaction system
- Logging system and other utility features<br>

## **Module Info**<br>
| Directory | Information |
|---|---|
|[`asset`](https://github.com/hexahero/gfxren/tree/master/3d_gfx_renderer/gfxback/asset)        |Functionality necessary for importing textures, constructing meshes and models. Model 3D transformations.|
|[`context`](https://github.com/hexahero/gfxren/tree/master/3d_gfx_renderer/gfxback/context)    |Provides application's front-end with components, needed to create window and rendering context. Interacts with operating system/window-specific stuff.   |
|[`gpudata`](https://github.com/hexahero/gfxren/tree/master/3d_gfx_renderer/gfxback/gpudata)    |Components allowing data transition between system and GPU memory. Data buffer creation.<br> Data upload and description. |
|[`input`](https://github.com/hexahero/gfxren/tree/master/3d_gfx_renderer/gfxback/input)        |Keyboard and mouse input handling. Key binding.|
|[`rendering`](https://github.com/hexahero/gfxren/tree/master/3d_gfx_renderer/gfxback/rendering)|Contains component responsible for drawing graphics and interaction with shader programs.|
|[`scene`](https://github.com/hexahero/gfxren/tree/master/3d_gfx_renderer/gfxback/scene)        |Provides transformations for camera-like behaviour.|
|[`shader`](https://github.com/hexahero/gfxren/tree/master/3d_gfx_renderer/gfxback/shader)      |Shader program compilation and linkage. Provides interface between C++ and GLSL programs.|
|[`util`](https://github.com/hexahero/gfxren/tree/master/3d_gfx_renderer/gfxback/util)          |Logging, exception handling etc.|

## **Roadmap**<br>
Nearest future
- Implement model import feature<br>
- GUI<br>
- Lighting and antialiasing<br>

Long-term perspective
- Basic physics<br>
- Software ray-tracing<br>
- Skeletal animations<br>
