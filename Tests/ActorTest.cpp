/**
 * @file ActorTest.cpp
 * @author Ben Zuke
 *
 * Actor Test
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <memory>
#include <Actor.h>
#include <PolyDrawable.h>
#include <Picture.h>

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

TEST(ActorTest, SetPicture)
{
    // Create a picture object
    auto picture = std::make_shared<Picture>();

    // Create an actor and add it to the picture
    auto actor = std::make_shared<Actor>(L"Actor");

    // Create a drawable for the actor
    auto drawable = std::make_shared<PolyDrawable>(L"Drawable");
    actor->SetRoot(drawable);
    actor->AddDrawable(drawable);

    picture->AddActor(actor);

    auto channel = drawable->GetAngleChannel();
    ASSERT_EQ(channel->GetTimeline(), picture->GetTimeline());
}

/** This tests that the animation of the position of an actor works */
TEST(ActorTest, Animation)
{
    // Create a picture object
    auto picture = std::make_shared<Picture>();

    // Create an actor and add it to the picture
    auto actor = std::make_shared<Actor>(L"Actor");
    picture->AddActor(actor);

    auto channel = actor->GetPositionChannel();

    // First we will ensure it works with no keyframes set
    picture->SetAnimationTime(0);
    actor->SetPosition(wxPoint(1234, 9833));

    // The channel should not be valid
    ASSERT_FALSE(channel->IsValid());

    // Getting a keyframe should not changle the position
    actor->GetKeyframe();
    ASSERT_EQ(1234, actor->GetPosition().x);
    ASSERT_EQ(9833, actor->GetPosition().y);

    // Now we'll set one keyframe and see if that works
    picture->SetAnimationTime(1.5);
    actor->SetPosition(wxPoint(101, 655));
    actor->SetKeyframe();

    // Change position
    actor->SetPosition(wxPoint(1234, 9833));
    ASSERT_EQ(1234, actor->GetPosition().x);
    ASSERT_EQ(9833, actor->GetPosition().y);

    // Wherever we move, now, the keyframe angle should be used
    picture->SetAnimationTime(0);
    ASSERT_EQ(101, actor->GetPosition().x);
    ASSERT_EQ(655, actor->GetPosition().y);

    actor->SetPosition(wxPoint(1234, 9833));
    picture->SetAnimationTime(1.5);
    ASSERT_EQ(101, actor->GetPosition().x);
    ASSERT_EQ(655, actor->GetPosition().y);

    actor->SetPosition(wxPoint(1234, 9833));
    picture->SetAnimationTime(3);
    ASSERT_EQ(101, actor->GetPosition().x);
    ASSERT_EQ(655, actor->GetPosition().y);

    // We'll set a second keyframe and see if that works
    picture->SetAnimationTime(3.0);
    actor->SetPosition(wxPoint(202, 1000));
    actor->SetKeyframe();

    // Test before the keyframes
    actor->SetPosition(wxPoint(1234, 9833));
    picture->SetAnimationTime(0);
    ASSERT_EQ(101, actor->GetPosition().x);
    ASSERT_EQ(655, actor->GetPosition().y);

    // Test at first keyframe
    actor->SetPosition(wxPoint(1234, 9833));
    picture->SetAnimationTime(1.5);
    ASSERT_EQ(101, actor->GetPosition().x);
    ASSERT_EQ(655, actor->GetPosition().y);

    // Test at second keyframe
    actor->SetPosition(wxPoint(1234, 9833));
    picture->SetAnimationTime(3);
    ASSERT_EQ(202, actor->GetPosition().x);
    ASSERT_EQ(1000, actor->GetPosition().y);

    // Test after second keyframe
    actor->SetPosition(wxPoint(1234, 9833));
    picture->SetAnimationTime(4);
    ASSERT_EQ(202, actor->GetPosition().x);
    ASSERT_EQ(1000, actor->GetPosition().y);

    // Test between the two keyframes
    actor->SetPosition(wxPoint(1234, 9833));
    picture->SetAnimationTime(2.25);
    ASSERT_EQ((101 + 202) / 2, actor->GetPosition().x);
    ASSERT_EQ((655 + 1000) / 2, actor->GetPosition().y);

    actor->SetPosition(wxPoint(1234, 9833));
    picture->SetAnimationTime(2.0);    // 1/3 between the two keyframes
    ASSERT_EQ((int)(101 + 1.0 / 3.0 * (202 - 101)), actor->GetPosition().x);
    ASSERT_EQ((int)(655 + 1.0 / 3.0 * (1000 - 655)), actor->GetPosition().y);
}
