#include "GameMath.h"

#include <algorithm>
#include <cmath>

namespace GameMath {
    glm::vec4 HSVToRGB(const glm::vec3& hsv)
    {
        const float hue = hsv.x - std::floor(hsv.x);
        const float saturation = std::clamp(hsv.y, 0.0f, 1.0f);
        const float value = std::clamp(hsv.z, 0.0f, 1.0f);
        const float chroma = value * saturation;
        const float hueSector = hue * 6.0f;
        const float x = chroma * (1.0f - std::abs(std::fmod(hueSector, 2.0f) - 1.0f));

        glm::vec3 rgb(0.0f);
        if (hueSector < 1.0f) {
            rgb = { chroma, x, 0.0f };
        } else if (hueSector < 2.0f) {
            rgb = { x, chroma, 0.0f };
        } else if (hueSector < 3.0f) {
            rgb = { 0.0f, chroma, x };
        } else if (hueSector < 4.0f) {
            rgb = { 0.0f, x, chroma };
        } else if (hueSector < 5.0f) {
            rgb = { x, 0.0f, chroma };
        } else {
            rgb = { chroma, 0.0f, x };
        }

        rgb += glm::vec3(value - chroma);
        return { rgb, 1.0f };
    }

    bool PointInTriangle(const glm::vec2& point, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c)
    {
        const float denominator = (b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y);
        if (std::abs(denominator) < 0.000001f) {
            return false;
        }

        const float alpha = ((b.y - c.y) * (point.x - c.x) + (c.x - b.x) * (point.y - c.y)) / denominator;
        const float beta = ((c.y - a.y) * (point.x - c.x) + (a.x - c.x) * (point.y - c.y)) / denominator;
        const float gamma = 1.0f - alpha - beta;
        return alpha >= 0.0f && beta >= 0.0f && gamma >= 0.0f;
    }

    std::uint32_t ScoreFromPosition(float x)
    {
        return x <= -10.0f ? 0u : static_cast<std::uint32_t>((x + 10.0f) / 10.0f);
    }

    float RotationFromVerticalVelocity(float velocity)
    {
        return std::clamp(velocity * 4.0f - 90.0f, -145.0f, -25.0f);
    }
}
