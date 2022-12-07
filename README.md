# **gfxren**
**Simplistic 3D graphics renderer implemented in C++ and OpenGL 3.3 API**<br>
Current project state: core functionality is implemented, awaiting further feature extension (in development)<br>

<img src='./meta/sponza_knight.png' width="30%"></img>
<img src='./meta/sponza_solid_color.png' width="30%"></img>
<img src='./meta/dna.png' width="30%"></img>
<br>Credits:
"Grey Knight" by LamedeFeu, "DNA" by Holoxica. (more at the end of the readme)

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
`F` - Toggle borderless fullscreen mode<br>
`G` - Toggle GUI<br>
`Mouse left button` - Camera control<br>
`Mouse right button` - Toggle cursor and camera mode<br>
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
|[`asset`](https://github.com/hexahero/gfxren/tree/master/src/gfxback/asset)        |Functionality necessary for importing textures, constructing meshes and models. Model 3D transformations.|
|[`context`](https://github.com/hexahero/gfxren/tree/master/src/gfxback/context)    |Provides application's front-end with components, needed to create window and rendering context. Interacts with operating system/window-specific stuff.   |
|[`gpudata`](https://github.com/hexahero/gfxren/tree/master/src/gfxback/gpudata)    |Components allowing data transition between system and GPU memory. Data buffer creation.<br> Data upload and description. |
|[`input`](https://github.com/hexahero/gfxren/tree/master/src/gfxback/input)        |Keyboard and mouse input handling. Key binding.|
|[`rendering`](https://github.com/hexahero/gfxren/tree/master/src/gfxback/rendering)|Contains component responsible for drawing graphics and interaction with shader programs.|
|[`scene`](https://github.com/hexahero/gfxren/tree/master/src/gfxback/scene)        |Provides transformations for camera-like behaviour.|
|[`shader`](https://github.com/hexahero/gfxren/tree/master/src/gfxback/shader)      |Shader program compilation and linkage. Provides interface between C++ and GLSL programs.|
|[`util`](https://github.com/hexahero/gfxren/tree/master/src/gfxback/util)          |Logging, exception handling etc.|

## **Roadmap**<br>
Nearest future
- Implement model import feature (implemented)<br>
- GUI (implemented)<br>
- Lighting and antialiasing (partially implemented)<br>

Long-term perspective
- Basic physics<br>
- Software ray-tracing<br>
- Skeletal animations<br>

<br>Credits to the authors of the assets used in this project<br>
"Grey Knight" (https://sketchfab.com/3d-models/grey-knight-0885c00ffa75478e9c6abe6b0370d285) by LamedeFeu (https://sketchfab.com/lamedefeu) licensed under CC-BY-4.0 (http://creativecommons.org/licenses/by/4.0/)<br>
"DNA" (https://sketchfab.com/3d-models/dna-60e95170b37549e3b45ee490b74bb112) by Holoxica (https://sketchfab.com/holoxica) licensed under CC-BY-4.0 (http://creativecommons.org/licenses/by/4.0/)<br>
