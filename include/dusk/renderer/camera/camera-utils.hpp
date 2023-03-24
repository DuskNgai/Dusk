#ifndef _DUSK_RENDERER_CAMERA_CAMERA_UTILS_HPP_
#define _DUSK_RENDERER_CAMERA_CAMERA_UTILS_HPP_

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

/// @see OrthographicCamera, PerspectiveCamera
enum class CameraType {
    Orthographic,
    Perspective,
};

/// @brief Convert Y field of view used in perspective cameras to width used in orthographic cameras.
float yfov_to_width(float y_fov, float distance, float aspect_ratio);

/// @brief Convert width used in orthographic cameras to Y field of view used in perspective cameras.
float width_to_yfov(float width, float distance, float aspect_ratio);

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_CAMERA_CAMERA_UTILS_HPP_
