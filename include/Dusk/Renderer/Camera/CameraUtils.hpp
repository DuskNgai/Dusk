#include <Dusk/Common.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief Convert Y field of view used in perspective cameras to width used in orthographic cameras.
float YFoVToWidth(float y_fov, float distance, float aspect_ratio);

/// @brief Convert width used in orthographic cameras to Y field of view used in perspective cameras.
float WidthToYFoV(float width, float distance, float aspect_ratio);

DUSK_NAMESPACE_END
