#include "GameMath.h"
#include <gtest/gtest.h>

TEST(PointInTriangle, DetectsInsideOutsideAndDegenerateTriangles)
{
    const glm::vec2 a{ 0.0f, 0.0f }, b{ 4.0f, 0.0f }, c{ 0.0f, 4.0f };
    EXPECT_TRUE(GameMath::PointInTriangle({ 1.0f, 1.0f }, a, b, c));
    EXPECT_TRUE(GameMath::PointInTriangle({ 0.0f, 0.0f }, a, b, c));
    EXPECT_FALSE(GameMath::PointInTriangle({ 3.0f, 3.0f }, a, b, c));
    EXPECT_FALSE(GameMath::PointInTriangle({ 1.0f, 0.0f }, a, { 1.0f, 0.0f }, { 2.0f, 0.0f }));
}

TEST(HSVToRGB, ConvertsPrimaryColoursAndWrapsHue)
{
    const glm::vec4 red = GameMath::HSVToRGB({ 0.0f, 1.0f, 1.0f });
    const glm::vec4 green = GameMath::HSVToRGB({ 1.0f / 3.0f, 1.0f, 1.0f });
    const glm::vec4 wrappedRed = GameMath::HSVToRGB({ 1.0f, 1.0f, 1.0f });
    EXPECT_FLOAT_EQ(red.r, 1.0f);
    EXPECT_FLOAT_EQ(red.g, 0.0f);
    EXPECT_NEAR(green.g, 1.0f, 0.0001f);
    EXPECT_FLOAT_EQ(wrappedRed.r, 1.0f);
}

TEST(Scoring, StartsAtZeroAndAdvancesEveryTenUnits)
{
    EXPECT_EQ(GameMath::ScoreFromPosition(-20.0f), 0u);
    EXPECT_EQ(GameMath::ScoreFromPosition(-10.0f), 0u);
    EXPECT_EQ(GameMath::ScoreFromPosition(0.0f), 1u);
    EXPECT_EQ(GameMath::ScoreFromPosition(20.0f), 3u);
}

TEST(PlayerRotation, IsClampedToReadableAngles)
{
    EXPECT_FLOAT_EQ(GameMath::RotationFromVerticalVelocity(0.0f), -90.0f);
    EXPECT_FLOAT_EQ(GameMath::RotationFromVerticalVelocity(100.0f), -25.0f);
    EXPECT_FLOAT_EQ(GameMath::RotationFromVerticalVelocity(-100.0f), -145.0f);
}
