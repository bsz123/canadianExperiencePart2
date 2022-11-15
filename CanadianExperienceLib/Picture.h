/**
 * @file Picture.h
 * @author Ben Zuke
 *
 * There will be one picture object that contains all of
 * our actors, which then contains the drawables.
 */

#ifndef CANADIANEXPERIENCE_PICTURE_H
#define CANADIANEXPERIENCE_PICTURE_H

class PictureObserver;
class Actor;

/**
 * Picture base class
 */
class Picture
{
private:

    /// The picture size
    wxSize mSize = wxSize(1500, 800);

    /// The observers of this picture
    std::vector<PictureObserver *> mObservers;

    /// Container of the actors in our image
    std::vector<std::shared_ptr<Actor>> mActors;

public:

    /**
     * Constructor
     */
    Picture() {}

    /// Copy Constructor (Disabled)
    Picture(const Picture &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Picture &) = delete;

    /**
     * Get the picture size
     * @return Picture size in pixels
     */
    wxSize GetSize() {return mSize;}

    /**
     * Set the picture size
     * @param size Picture size in pixels
     */
    void SetSize(wxSize size) {mSize = size;}

    void AddObserver(PictureObserver *observer);
    void RemoveObserver(PictureObserver *observer);
    void UpdateObservers();
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void AddActor(std::shared_ptr<Actor> actor);


    /**Iterate that iterates over actors in a picture*/
    class ActorIter
    {
    public:
        /** Constructor
         *  @param picture The picture we are iterating over
         *  @param pos Position in vector
         */
        ActorIter(Picture* picture, int pos) : mPicture(picture), mPos(pos) {}

        /**
         * Compare two Iterators
         * @param other The other iterator we are comparing to
         * @return  true if this position is not equal to the other position
        */
        bool operator!=(const ActorIter& other) const
        {
            return mPos != other.mPos;
        }

        /**
         * Get value at current position
         * @return Value at mPos in the collection
         */
        std::shared_ptr<Actor> operator *() const
        {
            return mPicture->mActors[mPos];
        }

        /**
         * Increment the iterator
         * @return Reference to this iterator */
        const ActorIter& operator++()
        {
            mPos++;
            return *this;
        }



    private:
        Picture* mPicture; ///< Picture iterated over
        int mPos; ///< Position in collection

    };

    ActorIter begin();


    ActorIter end();

};

#endif //CANADIANEXPERIENCE_PICTURE_H
