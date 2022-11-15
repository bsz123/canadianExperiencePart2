/**
 * @file PictureObserver.h
 * @author Ben Zuke
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */

#ifndef CANADIANEXPERIENCE_PICTUREOBSERVER_H
#define CANADIANEXPERIENCE_PICTUREOBSERVER_H

class Picture;

/**
 * Observes and tells us about the image
 */
class PictureObserver
{
private:

    /// Picture we are observing
    std::shared_ptr<Picture> mPicture;

public:

    /// Copy Constructor (Disabled)
    PictureObserver(const PictureObserver &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const PictureObserver &) = delete;

    virtual ~PictureObserver();

    /// Virtual function for our observers
    virtual void UpdateObserver() = 0;

    /**
     * Get the picture we are observing
     * @return shared pointer of the observer's picture
     */
    std::shared_ptr<Picture> GetPicture() { return mPicture; }

    void SetPicture(std::shared_ptr<Picture> picture);

protected:
    /// Constructor
    PictureObserver() {}

};

#endif //CANADIANEXPERIENCE_PICTUREOBSERVER_H
