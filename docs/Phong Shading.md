# Phong Shading

## Phong Lighting Model

Phong Lighting Model 的主要结构由3个分量组成：环境(Ambient)、漫反射(Diffuse)和镜面(Specular)光照

- 环境光照：即使在黑暗的情况下，世界上通常也仍然有一些光亮（月亮、远处的光），所以物体几乎永远不会是完全黑暗的。为了模拟这个，我们会使用一个环境光照常量，它永远会给物体一些颜色。

- 漫反射光照：模拟光源对物体的方向性影响(Directional Impact)。它是冯氏光照模型中视觉上最显著的分量。物体的某一部分越是正对着光源，它就会越亮。

- 镜面光照：模拟有光泽物体上面出现的亮点。镜面光照的颜色相比于物体的颜色会更倾向于光的颜色。

其公式如下：

$$
I_p=\underbrace{k_ai_a}_{\text{ambient}}+\sum_{m\in\text{lights}}(\underbrace{k_d(\hat{L}_m\cdot\hat{N})i_{m,d}}_{\text{diffuse}}+\underbrace{k_{s}(\hat{R}_m\cdot\hat{V})^{\alpha}i_{m,s}}_{\text{specular}})
$$

|   Symbol    |       Description        |
| :---------: | :----------------------: |
|    $I_p$    |        像素的颜色        |
|    $k_a$    |        环境光因子        |
|    $i_a$    |        环境光强度        |
|    $k_d$    |        漫反射因子        |
| $\hat{L}_m$ |     物体到光源的方向     |
|  $\hat{N}$  |        物体法向量        |
|  $i_{m,d}$  |     光源漫反射光强度     |
|    $k_s$    |      镜面反射光因子      |
| $\hat{R}_m$ | 光线在物体表面反射的方向 |
|  $\hat{V}$  |       相机视角方向       |
|  $\alpha$   |          反光度          |
|  $i_{m,s}$  |    光源镜面反射光强度    |

其中，$k_a$, $k_d$, $k_s$, $\alpha$ 是物体的材质属性，$i_a$, $i_{m,d}$, $i_{m,s}$ 是光源属性。
