/**
 * @file AnimChannelAngleTest.cpp
 * @author Ben Zuke
 *
 * Simple tests on our anim channel angles
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <AnimChannelAngle.h>

using namespace std;

class AnimMock : public AnimChannelAngle
{
public:
    AnimMock() {}

};


TEST(AnimChannelAngleTest, Name)
{

    AnimMock anim;

    anim.SetName(L"TestName");

    ASSERT_EQ(L"TestName", anim.GetName());

}
