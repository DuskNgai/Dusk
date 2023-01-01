# Dusk Engine

Dusk 引擎是作为我各个图形学项目的基础渲染器。当前的实现完全基于 C++ 和 OpenGL。

## Keyboard & Mouse Mapping

## Plan

1. 一个 3-D 渲染器，支持一般的 OpenGL 渲染。（Dusk）
    1. 文件管理系统。
    2. 基于 `ImGui` 的比较好的 UI 界面。
2. 一个 3-D 神经网络渲染器，支持基于 CUDA 的神经辐射场（NeRF）渲染。(Mod-NeRF)
    1. GPU Memory
    2. Encoding
    3. Loss
    4. Optimizer
    5. Network
3. 一个 2-D 图片查看器，支持一般的图像格式。（Image-Viewer）
    1. LDR: PNG, JPG, TIFF。
    2. HDR: EXR, HDR。
4. 一个 3-D 光追渲染器，支持基于 Cpp/CUDA/Vulkan 的渲染。（PBR-Renderer）
    1. Cpp 实现的 PBRT。
    2. 实现 Vulkan + CUDA 的 ReSTIR。

## Reference

1. [TheCherno 的游戏引擎教学](https://www.youtube.com/watch?v=vtWdgtMo1T4)
2. [TheCherno 的游戏引擎代码](https://github.com/TheCherno/Hazel)
3. [Inviwo](https://inviwo.org)