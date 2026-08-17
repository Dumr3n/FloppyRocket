#pragma once

#include <glm/glm.hpp>
#include <cstdint>

namespace GameMath {
    glm::vec4 HSVToRGB(const glm::vec3& hsv);
    bool PointInTriangle(const glm::vec2& point, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c);
    std::uint32_t ScoreFromPosition(float x);
    float RotationFromVerticalVelocity(float velocity);
}
