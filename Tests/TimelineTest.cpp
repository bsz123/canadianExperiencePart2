/**
 * @file TimelineTest.cpp
 * @author Ben Zuke
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Timeline.h>

TEST(TimelineTest, NumFrameInit)
{
    Timeline timeline;

    // Default value
    ASSERT_EQ(300, timeline.GetNumFrames());
}

TEST(TimelineTest, FrameRateInit)
{
    Timeline timeline;

    // Default value
    ASSERT_EQ(30, timeline.GetFrameRate());
}

TEST(TimelineTest, CurrentTimeInit)
{
    Timeline timeline;

    // Default value
    ASSERT_NEAR(0, timeline.GetCurrentTime(), .0001);

}

TEST(TimelineTest, GetDuration)
{
    Timeline timeline;

    // Default value
    ASSERT_NEAR(10, timeline.GetDuration(), 0.0001);

    // Changed duration
    timeline.SetFrameRate(375);
    ASSERT_NEAR(300.0 / 375.0, timeline.GetDuration(), 0.0001);

    timeline.SetNumFrames(789);
    ASSERT_NEAR(789.0 / 375.0, timeline.GetDuration(), 0.0001);
}

TEST(TimelineTest, GetCurrentFrame)
{
    Timeline timeline;

    // Default value
    ASSERT_EQ(0, timeline.GetCurrentFrame());

    // Changed time
    timeline.SetCurrentTime(9.27);
    ASSERT_EQ(278, timeline.GetCurrentFrame());
}
