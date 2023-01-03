# Coordinate Space

## Coordinate space

`OpenGL` 中的坐标空间有五种：

1. Local Space, $\mathbb{R}^3$. 局部坐标系是指物体所在的坐标坐标系，即对象最开始所在的地方。
2. World Space, $\mathbb{R}^3$. 世界坐标系是指物体相对于世界的坐标。
3. View/Camera/Eye Space, $\mathbb{R}^3$. 观察坐标系是将世界坐标系坐标转化为用户视野前方的坐标而产生的结果。
4. Clip Space, $[-1,1]^3$. 在 `Vertex Shader` 运行的最后，`OpenGL` 期望所有的坐标都能落在一个特定的范围内，且任何在这个范围之外的点都应该被裁剪掉。
5. Screen Space, $[-1,1]^2$.

## Model Transformations

模型矩阵是一种变换矩阵，它对物体进行缩放、旋转、位移，将物体从局部坐标系映射到世界坐标系。

### Scaling Transformations

$$
S(\mathbf{s})=\begin{bmatrix}s_x&0&0&0\\0&s_y&0&0\\0&0&s_z&0\\0&0&0&1\\\end{bmatrix}
$$

### Rotation Transformations

沿坐标轴旋转：
$$
R_x(\theta)=\begin{bmatrix}1&0&0&0\\0&\cos\theta&-\sin\theta&0\\0&\sin\theta&\cos\theta&0\\0&0&0&1\\\end{bmatrix}\\
R_y(\phi)=\begin{bmatrix}\cos\phi&0&\sin\phi&0\\0&1&0&0\\-\sin\phi&0&\cos\phi&0\\0&0&0&1\\\end{bmatrix}\\
R_z(\gamma)=\begin{bmatrix}\cos\gamma&-\sin\gamma&0&0\\\sin\gamma&\cos\gamma&0&0\\0&0&1&0\\0&0&0&1\\\end{bmatrix}\\
$$
沿任意向量 $\mathbf{a}=(a_x,a_y,a_z)$​ 旋转：
$$
R(\mathbf{a},\theta)=\begin{bmatrix}
\cos\theta+a_x^2(1-\cos\theta)&a_xa_y(1-\cos\theta)-a_z\sin\theta&a_xa_z(1-\cos\theta)+a_y\sin\theta&0\\
a_ya_x(1-\cos\theta)+a_z\sin\theta&\cos\theta+a_y^2(1-\cos\theta)&a_ya_z(1-\cos\theta)-a_x\sin\theta&0\\
a_za_x(1-\cos\theta)-a_y\sin\theta&a_za_y(1-\cos\theta)+a_x\sin\theta&\cos\theta+a_z^2(1-\cos\theta)&0\\
0&0&0&1\\\end{bmatrix}\\
$$

### Translation Transformations

$$
T(\mathbf{t})=\begin{bmatrix}1&0&0&t_1\\0&1&0&t_2\\0&0&1&t_3\\0&0&0&1\\\end{bmatrix}
$$

### Model Transformations

模型矩阵的作用顺序是先缩放，再旋转，再平移。
$$
M=T(\mathbf{t})R(\theta,\phi,\gamma)S(\mathbf{s})
$$
本质上，模型矩阵的数值是世界坐标系的基用局部坐标系的基的线性表示。

## View Transformations

观察矩阵是一种变换矩阵，它对物体进行旋转、位移，将物体从世界坐标系映射到观察坐标系。观察坐标系是一种特殊的局部坐标系，因此可以看作是无缩放的模型矩阵的逆变换，即先平移到相机所在的位置，再旋转到相机的朝向。

由相机的朝向 $\mathbf{v}$，相机的参考向上方向 $\mathbf{u}$，我们可以得到相机的局部坐标系：
$$
\begin{align*}
\mathbf{e}_x&=\mathbf{v}\times\mathbf{u}\\
\mathbf{e}_y&=\mathbf{e}_x\times\mathbf{v}\\
\mathbf{e}_z&=-\mathbf{v}
\end{align*}
$$
结合相机所在的位置 $\mathbf{p}$，对应的观察矩阵是：
$$
V=\begin{bmatrix}
\mathbf e_{x_{x}}&\mathbf e_{x_{y}}&\mathbf e_{x_{z}}&0\\
\mathbf e_{y_{x}}&\mathbf e_{y_{y}}&\mathbf e_{y_{z}}&0\\
\mathbf e_{z_{x}}&\mathbf e_{z_{y}}&\mathbf e_{z_{z}}&0\\
0&0&0&1
\end{bmatrix}\begin{bmatrix}
1&0&0&-\mathbf p_x\\
0&1&0&-\mathbf p_y\\
0&0&1&-\mathbf p_z\\
0&0&0&1
\end{bmatrix}=R^{-1}_{x,y,z}(\theta)T^{-1}(\mathbf p)
$$
或者为：
$$
\begin{align*}
V&=\left(\begin{bmatrix}
1&0&0&\mathbf p_x\\
0&1&0&\mathbf p_y\\
0&0&1&\mathbf p_z\\
0&0&0&1
\end{bmatrix}
\begin{bmatrix}
\mathbf e_{x_{x}}&\mathbf e_{y_{x}}&\mathbf e_{z_{x}}&0\\
\mathbf e_{x_{y}}&\mathbf e_{y_{y}}&\mathbf e_{z_{y}}&0\\
\mathbf e_{x_{z}}&\mathbf e_{y_{z}}&\mathbf e_{z_{z}}&0\\
0&0&0&1
\end{bmatrix}\right)^{-1}\\
&=\begin{bmatrix}
\mathbf e_{x_{x}}&\mathbf e_{y_{x}}&\mathbf e_{z_{x}}&\mathbf p_x\\
\mathbf e_{x_{y}}&\mathbf e_{y_{y}}&\mathbf e_{z_{y}}&\mathbf p_y\\
\mathbf e_{x_{z}}&\mathbf e_{y_{z}}&\mathbf e_{z_{z}}&\mathbf p_z\\
0&0&0&1
\end{bmatrix}^{-1}\\
&=[T(\mathbf p)R_{x,y,z}(\theta)]^{-1}
\end{align*}
$$

### View Transformations

## Projection Transformations

为了将顶点坐标从观察坐标系变换到裁剪坐标系，我们需要定义一个投影矩阵，它指定了一个范围的坐标。接着它会将在这个指定的范围内的坐标变换为标准化设备坐标（Normalized Device Coordinate）的范围 $[-1,1]^3$。

### Orthographic Projection

将坐标进行如下映射，x: $[l,r]\to[-1,1]$, y: $[b,t]\to[-1,1]$, **z: $[-f,-n]\to[1,-1]$**，之后裁剪掉  $[-1,1]^3$ 范围外的顶点。
$$
\begin{align*}
x_n&=\frac{2x_e}{r-l}-\frac{r+l}{r-l}\\
y_n&=\frac{2y_e}{t-b}-\frac{t+b}{t-b}\\
z_n&=-\frac{2z_e}{f-n}-\frac{f+n}{f-n}\\
\end{align*}
$$
因此，正交投影矩阵 $M_{O\to C}$ 为：
$$
M_{O\to C}=\begin{bmatrix}
\frac{2}{r-l}&0&0&-\frac{r+l}{r-l}\\
0&\frac{2}{t-b}&0&-\frac{t+b}{t-b}\\
0&0&-\frac{2}{f-n}&-\frac{f+n}{f-n}\\
0&0&0&1\\
\end{bmatrix}
$$

### Perspective Projection

首先将透视投影的平截头体变换成正交投影的立方体，由相似性可得：
$$
E:(x_e,y_e,z_e)\to N:(-\frac{n}{z_e}x_e,-\frac{n}{z_e}y_e,z_e)\\
z_e<0,0<n<f
$$
因此该矩阵 $M_{P\to O}$ 满足：
$$
M_{P\to O}\begin{bmatrix}x_e\\y_e\\z_e\\1\\\end{bmatrix}
=\begin{bmatrix}-nx_e/z_e\\-ny_e/z_e\\z_e\\1\\\end{bmatrix}
=\begin{bmatrix}nx_e\\ny_e\\-z^2_e\\-z_e\\\end{bmatrix}
$$
最后一个等号是因为在齐次坐标系中。因此矩阵 $M_{P\to O}$ 满足如下形式：
$$
M_{P\to O}=\begin{bmatrix}
n&0&0&0\\
0&n&0&0\\
0&0&A&B\\
0&0&-1&0\\
\end{bmatrix}
$$
由于：
$$
A(-n)+B=-n^2\\
A(-f)+B=-f^2
$$
因此：
$$
M_{P\to O}=\begin{bmatrix}
n&0&0&0\\
0&n&0&0\\
0&0&n+f&fn\\
0&0&-1&0\\
\end{bmatrix}
$$
因此我们可以得到透视投影的矩阵
$$
\begin{align*}
M_{P\to C}&=M_{O\to C}M_{P\to O}\\
&=\begin{bmatrix}
\frac{2}{r-l}&0&0&-\frac{r+l}{r-l}\\
0&\frac{2}{t-b}&0&-\frac{t+b}{t-b}\\
0&0&-\frac{2}{f-n}&-\frac{f+n}{f-n}\\
0&0&0&1\\
\end{bmatrix}\begin{bmatrix}
n&0&0&0\\
0&n&0&0\\
0&0&n+f&fn\\
0&0&-1&0\\
\end{bmatrix}\\
&=\begin{bmatrix}
\frac{2n}{r-l}&0&\frac{r+l}{r-l}&0\\
0&\frac{2n}{t-b}&\frac{t+b}{t-b}&0\\
0&0&-\frac{f+n}{f-n}&-\frac{2fn}{f-n}\\
0&0&-1&0\\
\end{bmatrix}
\end{align*}
$$
