#include <cmath>

#include <glm/glm.hpp>

#include <Dusk/Renderer/Camera/CameraUtils.hpp>

DUSK_NAMESPACE_BEGIN

float YFoVToWidth(float y_fov, float distance, float aspect_ratio) {
    return 2.0f * distance * std::tan(glm::radians(y_fov) * 0.5f) * aspect_ratio;
}

float WidthToYFoV(float width, float distance, float aspect_ratio) {
    return glm::degrees(2.0f * std::atan(width / (2.0f * distance * aspect_ratio)));
}

DUSK_NAMESPACE_END
