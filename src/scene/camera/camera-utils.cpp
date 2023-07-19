#include <cmath>

#include <glm/glm.hpp>

#include <dusk/scene/camera/camera-utils.hpp>

DUSK_NAMESPACE_BEGIN

float yfov_to_width(float y_fov, float distance, float aspect_ratio) {
    return 2.0f * distance * std::tan(glm::radians(y_fov) * 0.5f) * aspect_ratio;
}

float width_to_yfov(float width, float distance, float aspect_ratio) {
    return glm::degrees(2.0f * std::atan(width / (2.0f * distance * aspect_ratio)));
}

DUSK_NAMESPACE_END
