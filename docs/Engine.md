# Dusk Engine

**Dusk 引擎**主要参考了[TheCherno 的游戏引擎教学](https://www.youtube.com/watch?v=vtWdgtMo1T4)以及它的[代码](https://github.com/TheCherno/Hazel)。本文档用于记录实现时候个部分的具体作用。想到用游戏引擎做渲染器的原因是，游戏引擎和 Mod-NeRF 所需的渲染器都需要实现渲染和交互的功能，因此二者不谋而合。本引擎所需实现的功能是：
1. 一个用 `OpenGL` 与 `ImGui` 实现的窗口（window）。
2. 一个将用户输入传到对应层级（layer）的事件系统（event system）。
3. 一个对外的 `Application` 接口，用户只需要继承并且实现对应的类方法即可使用图形交互功能。

## Core

`Core` 文件夹下存放了渲染器的核心部件，包括了主程序 `Application`，相机 `Camera`，事件 `Event` 和窗口 `Window`。

### Application

`Application` 类是引擎运行的载体。`Application` 类内含了一个 `Window` 类和多个 `Layer` 类。其中，`Window` 类是专门用于管理窗口的。而一切需要额外实现且于引擎关系不大的功能模块，都可以通过继承 `Layer` 类实现。

#### Layer

`Layer` 类是引擎应用和用户应用的具体实现类。我们一般用栈（事实上用 `std::vector` 实现）存储所有的层级，因此 `Application` 类内含一个层级栈（`LayerStack`）。层级栈由两部分组成，上层是若干个普通层级，下层是若干个叠加层级。程序运行时候，特别是窗口运行的时候，层级栈的更新方向是从上到下，而事件的处理方向从下到上。这是因为显示在屏幕上的时候，越下层的层级的图像会被绘制在窗口的越上层，当用户发出交互请求时候，通常是与当前最上层的图层交互，因此事件需要从下往上层处理。下层的叠加层级一般是用于 `debug` 的层级。

#### ImGui Layer

`ImGui Layer` 类是一个特殊的 `Layer`，专门用于在每一帧初始化和销毁 `ImGui` 。事实上，每一 `Layer` 都有一个处理自己层 `ImGui` 有关的函数，即 `OnImGuiRender`。我们在这个函数中规定 `ImGui` 的窗口排布并且绑定成员变量，以方便交互窗口的统一绘制。

### Window

`Window` 类是图形界面交互的核心，用于接收用户输入，展示用户所需的输出。

#### Input System

输入系统采用的是轮询（Polling）的方法，每次调用 `Input` 类的函数时候，都会向更底层的 `GLFW` 发出是否有输入的问询。

### Event System

`Event` 类记录了用户从窗口发出的一系列交互请求。`Application` 类创造了 `Window` 类，但 `Window` 类并不知道 `Application` 类的存在，只得到了一个回调函数。当用户与窗口交互时候产生这些事件会被窗口记录下来，随后窗口调用回调函数，即这些事件通过这种方式交由 `Application` 类来处理。

如果一个事件被某个函数最终处理完了，那么这个事件将不再会被后续的函数处理。

## Graphics Interfaces or Renderer

引擎所想要达到的效果是跨平台的渲染，但图形 API（OpenGL, Vulkan, DirectX ...）则是跟平台有关的。图形 API 提供了具体的操作，而我们需要用这些具体的操作实现一些图形学中的一些更大的概念。因此引擎会对于图形 API 进行一层抽象封装。这里我们使用的是最简单容易学的 `OpenGL` 的 `glad` + `glfw`。简单来说，`glad` 是比较新的加载函数库，由于 `OpenGL` 驱动版本众多，它大多数函数的位置都无法在编译时确定下来，需要在运行时查询；`glfw` 是窗口工具库，它提供了一些渲染物体所需的最低限度的接口。

### Renderer

Renderer 由负责场景搭建的 `Renderer` 和负责具体渲染的 `RendererAPI` + `RenderCommand` 组成。`Renderer` 主要功能是创建场景的元素，包括相机，材质，集合体等。`RendererAPI` 内部的 `s_API` 定义了渲染器使用的图形 API。同时，`RendererAPI` 也封装了渲染的基本操作，如 `ClearColor` ，`draw_arrays`，`draw_elements`。`RenderCommand` 是对 `RendererAPI` 的再一次封装，把 `RendererAPI` 的类方法变成了静态函数，是常用的封装手段。

### Vertex/Element Buffer

Vertex Buffer 就是存储数据的地方，以 OpenGL 为例就是 vertex buffer object (VBO) 和 element buffer object (EBO)，我们需要有把内存上的数据传输到显存上的接口，激活或者失活 buffer 的接口（以便我们在运行时候改变渲染对象）等等。

### Buffer Layout & Vertex Array

Buffer Layout 就是如何解释 buffer 中的数据的意义，在 OpenGL 中就是通过 vertex array buffer (VAO) 与 shader 进行通信。Vertex array 会存储 vertex buffer 的指针和 index buffer 的指针指定渲染的数据。这里我们模仿 OpenGL vertex array 的做法，即一个 vertex array 可以存储多个 vertex buffer 和一个 index buffer。

### Shader

Shader 是一个 GPU 上的程序。在 OpenGL 中，主要的 Shader 是 Vertex Shader 和 Fragment Shader，具体作用就不在这里介绍了。这里我们还创建了一个 `ShaderLibrary` 以便于管理和使用 Shader 。

### Camera System

相机系统在 3-D 渲染中是至关重要的。相机记录了空间坐标系的变换，使得几何物体能被多视角观测。我们的引擎必须要实现 perspective 的相机和 orthographic 的相机，以便于后续使用。当前相机记录了

- look from, look to, look up 与相机在空间中的位姿有关信息。
- near plane, far plane, aspect ratio 与相机的投影有关信息。
- view matrix, projection matrix 及其逆矩阵等相机的视角矩阵，投影矩阵有关信息。

**TODO**：当前相机的旋转是基于欧拉角的，后续需要改成四元数。

#### Perspective Camera

Perspective camera 多了 field of view 信息，以便得到 perspective 投影下的投影矩阵。

#### Orthographic Camera

Perspective camera 多了窗口的 width 信息，以便得到 orthographic 投影下的投影矩阵。

### Texture

Texture 是存储图像或者需要插值矩阵的地方。我们的引擎暂时支持 2D 的纹理。

### Framebuffer

Framebuffer 是画板，存储需要画布（Texture、Renderbuffer）。

## Entity Component System

被渲染的物体需要知道自己所处的场景，以及场景中的别的物体，以完成碰撞检测之类的事情。因此我们需要一个管理物体的系统即 Entity Component System。采用 Array of Structure 的效率会更高。其中 Structure 是一个 Entity，它包含了各种 Component。

## Others

### Log System

`Log` 类是对第三方的日志库的封装，目的是为了不把第三方库的接口直接暴露给用户，且日后替换第三方库时能尽可能的方便。

### Timer

`Timer` 类是简易的计时器和时钟系统。计时器包含了开始、暂停、停止、读数、重置功能。时钟包含了更新每帧之间时间差和获取当前时间的功能。

**当前计时器和时钟系统合二为一了，但可能会存在潜在的 bug，日后会将二者分开。**

