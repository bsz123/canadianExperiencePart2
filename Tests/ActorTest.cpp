/**
 * @file ActorTest.cpp
 * @author Ben Zuke
 *
 * Actor Test
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Actor.h>

using namespace std;

TEST(ActorTest, Constructor)
{
    Actor actor(L"Harold");
    ASSERT_EQ(std::wstring(L"Harold"), actor.GetName());
}

TEST(ActorTest, EnabledDefault)
{
    Actor actor(L"Harold");
    ASSERT_TRUE(actor.IsEnabled()); // Test Default Value Enabled

    actor.SetEnabled(false); // Test Setter
    ASSERT_FALSE(actor.IsEnabled()); // Test Getter after change

    actor.SetEnabled(true); // Test Setter
    ASSERT_TRUE(actor.IsEnabled()); // Test Getter after change

}

TEST(ActorTest, Clickable)
{
    Actor actor(L"Harold");
    ASSERT_TRUE(actor.IsClickable()); // Test Default Value

    actor.SetClickable(false); // Test Setter
    ASSERT_FALSE(actor.IsClickable()); // Test Getter after change

    actor.SetClickable(true); // Test Setter
    ASSERT_TRUE(actor.IsClickable()); // Test Getter after change

}

TEST(ActorTest, DefaultPosition)
{
    Actor actor(L"Harold");
    ASSERT_EQ(wxPoint(0,0), actor.GetPosition()); // Test Default Value

    actor.SetPosition(wxPoint(4,4)); // Test Setter
    ASSERT_EQ(wxPoint(4,4),actor.GetPosition()); // Test Getter after change

}
