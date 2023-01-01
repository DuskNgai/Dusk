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
