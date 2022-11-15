/**
 * @file PictureObserver.cpp
 * @author Ben Zuke
 *
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */

#include "pch.h"
#include <memory>

#include "PictureObserver.h"
#include "Picture.h"


/**
 * Destructor
 *
 * Must be declared as virtual:
 * virtual ~PictureObserver();
 */
PictureObserver::~PictureObserver()
{
    if (mPicture != nullptr)
    {
        mPicture->RemoveObserver(this);
    }
}

/**
 * Set the picture for this observer
 * @param picture The picture to set
 */
void PictureObserver::SetPicture(std::shared_ptr<Picture> picture)
{
    mPicture = picture;
    mPicture->AddObserver(this);
}
