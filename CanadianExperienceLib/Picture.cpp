/**
 * @file Picture.cpp
 * @author Ben Zuke
 *
 * The picture we are drawing.
 *
 * There will be one picture object that contains all of
 * our actors, which then contains the drawables.
 */

#include "pch.h"
#include "Actor.h"
#include "Picture.h"
#include "PictureObserver.h"


/**
 * Add an observer to this picture.
 * @param observer The observer to add
 */
void Picture::AddObserver(PictureObserver* observer)
{
    mObservers.push_back(observer);
}

/**
 * Remove an observer from this picture
 * @param observer The observer to remove
 */
void Picture::RemoveObserver(PictureObserver* observer)
{
    auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
    if (loc != std::end(mObservers))
    {
        mObservers.erase(loc);
    }
}

/**
 * Update all observers to indicate the picture has changed.
 */
void Picture::UpdateObservers()
{
    for (auto observer : mObservers)
    {
        observer->UpdateObserver();
    }
}


/**
 * Draw this picture on a device context
 * @param graphics The device context to draw on
 */
void Picture::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto actor : mActors)
    {
        actor->Draw(graphics);
    }

}

/**
 * Add an actor to the picture
 * @param actor
 */
void Picture::AddActor(std::shared_ptr<Actor> actor)
{
    mActors.push_back(actor);
    actor->SetPicture(this);
}

/**
 * Begin iterator
 * @return Iterator at beginning of vector
 */
Picture::ActorIter Picture::begin()
{
    return ActorIter(this, 0);
}

/**
 * Iterator for end of collection
 * @return Iter object at end of vector
 */
Picture::ActorIter Picture::end()
{

    return ActorIter(this, mActors.size());
}
