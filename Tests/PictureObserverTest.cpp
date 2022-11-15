/**
 * @file PictureObserverTest.cpp
 * @author Ben Zuke
 *
 * Observer test
 */

#include <pch.h>
#include <PictureObserver.h>
#include <Picture.h>
#include "gtest/gtest.h"



class PictureObserverMock : public PictureObserver
{
public:
    PictureObserverMock() : PictureObserver() {}

    bool mUpdated = false;

    virtual void UpdateObserver() override { mUpdated = true; }

};

TEST(PictureObserverTest, Construct) {
    PictureObserverMock observer;
}

TEST(PictureObserverTest, OneObserver) {
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;

    // And set it for the observer:
    observer.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_TRUE(observer.mUpdated);
}

TEST(PictureObserverTest, ManyObserver)
{
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create multiple mock observer objects
    PictureObserverMock observer1;
    PictureObserverMock observer2;

    observer1.SetPicture(picture);
    observer2.SetPicture(picture);

    picture->UpdateObservers();

    // Assert UpdateObserver is called on both
    ASSERT_TRUE(observer1.mUpdated);
    ASSERT_TRUE(observer2.mUpdated);

}

TEST(PictureObserverTest, PictureGet)
{
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;

    // And set it for the observer:
    observer.SetPicture(picture);

    auto pictureGot = observer.GetPicture();

    ASSERT_EQ(picture, pictureGot);

}


TEST(PictureObserverTest, Destructor)
{
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create multiple mock observer objects
    PictureObserverMock observer1;

    observer1.SetPicture(picture);

    // Assure observer working
    ASSERT_FALSE(observer1.mUpdated);

    picture->UpdateObservers();

    {
        PictureObserverMock observer2;
        observer2.SetPicture(picture);

        ASSERT_TRUE(observer1.mUpdated);

        ASSERT_FALSE(observer2.mUpdated);

    }

    // Check if another observer is destroyed that the remaining works fine
    ASSERT_TRUE(observer1.mUpdated);

}
