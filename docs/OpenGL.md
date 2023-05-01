# OpenGL Knowledges

## Core Profile and Compatibility Profile

`OpenGL` 有两种模式，一种是 `Core Profile`，一种是 `Compatibility Profile`。`Core Profile` 是 `OpenGL 3.2` 之后的版本，`Compatibility Profile` 是 `OpenGL 3.2` 之前的版本。二者的区别在于，`Core Profile` 对一些过时的函数会报错；而 `Compatibility Profile` 则不会。

`Compatibility Profile` 下会有一个默认的 `Vertext Array Object`；而 `Core Profile` 则没有，因此在 `Core Profile` 下，需要手动创建一个 `Vertex Array Object`。

## glad

```
#error OpenGL header already included, remove this include, glad already provides it.
```

这是因为 `glad.h` 需要放在所有 `OpenGL` 文件的最前面，因此在多重头文件的代码中，由于每个头文件都可能会包含 `glad.h`，因此 `glfw3.hpp` 要被放到最后去。

## `glGen*()` and `glCreate*()`

`OpenGL` 在 4.5 版本之后，为所有 `glGen*()` 函数增加了 `glCreate*()` 版本的函数。二者的区别在于，`glGen*()` 函数只有在 `glBind*()` 函数被调用之后，才会真正的创建对象；而 `glCreate*()` 函数则会立即创建对象。

## Delete Shader

调用了 `glDeleteShader` 后，如果 `shader` 对象连接在一个 `program` 对象上，它将被标记为删除，但是在它不再连接在任何 `program` 对象上之前，对于任何渲染环境来说，它都不会被删除（也就是说，它必须从它所连接的地方分离（`detach`）出来，才会被删除）。

如果 `shader` 已经因为 `glDeleteShader` 而标记为删除，并且它没有附加（`attach`）到任何 `program` 对象，那么它将在被分离后被删除。

## Depth Testing

Depth Buffer 是在 Fragment Shader 运行之后在屏幕空间中运行的。`gl_FragCoord` 的 `x` 和 `y` 分量代表了片段的屏幕空间坐标，`z` 分量代表了片段的深度值。

实际的运算中，NDC 空间中的深度不是线性变化的，而是调和线性变化的，即，深度值在近平面附近变化很快，在远平面附近变化很慢。这是主要为了适应 `float` 类型的精度变化。

### Z-fighting

Depth Buffer 没有足够的精度来决定两个图形哪个在前面，会产生交替的闪烁现象。

解决方法：
1. 永远不要把多个物体摆得太靠近；
2. 尽可能将近平面设置远一些；
3. 使用更高精度的深度缓冲

## Stencil Testing

Stencil Buffer 是一个与 Depth Buffer 类似的缓冲，在深度测试之前运行。`glfw` 会自动配置一个模板缓冲。

## Blending

当写入深度缓冲时，深度缓冲不会检查片段是否是透明的，所以透明的部分会和其它值一样写入到深度缓冲中。即使透明的部分应该显示背后的物体，深度测试仍然丢弃了它们。一个简单的解决方法是由远及近地渲染所有的透明物体。
