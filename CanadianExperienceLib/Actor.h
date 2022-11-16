/**
 * @file Actor.h
 * @author Ben Zuke
 *
 * Class for actors in our drawings.
 */

#ifndef CANADIANEXPERIENCE_ACTOR_H
#define CANADIANEXPERIENCE_ACTOR_H

#include "AnimChannelPoint.h"

class Drawable;
class Picture;

/**
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */
class Actor
{
private:
    /// Actor name
    std::wstring mName;

    /// Is enabled
    bool mEnabled = true;

    /// Actor Position
    wxPoint mPosition = wxPoint(0,0);

    /// Is Clickable
    bool mClickable = true;

    /// The root drawable
    std::shared_ptr<Drawable> mRoot;

    /// The drawables in drawing order
    std::vector<std::shared_ptr<Drawable>> mDrawablesInOrder;

    /// The picture that Actor belongs to
    Picture* mPicture = nullptr;

    /// The Channel this Actor is part of
    AnimChannelPoint mAnimChannel;

public:

    /// Destructor
    virtual ~Actor() {};

    Actor(const std::wstring &name);

    /// Default constructor (disabled)
    Actor() = delete;

    /// Copy constructor (disabled)
    Actor(const Actor &) = delete;

    /// Assignment operator
    void operator=(const Actor &) = delete;

    void SetRoot(std::shared_ptr<Drawable> root);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    std::shared_ptr<Drawable> HitTest(wxPoint pos);

    void AddDrawable(std::shared_ptr<Drawable> drawable);

    /**
     * Get the actor name
     * @return Actor name
     */
    std::wstring GetName() const { return mName; }

    /**
     * Get the actor position as point
     * @return actor position as point
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * The actor position
     * @param pos The new actor position
     */
    void SetPosition(wxPoint pos) {mPosition = pos;}

    /**
     * Actor is enabled
     * @return enabled status
     */
    bool IsEnabled() const { return mEnabled; }

    /**
     * Set Actor Enabled
     * @param enabled New enabled status
     */
    void SetEnabled(bool enabled) { mEnabled = enabled; }

    /**
     * Actor is clickable
     * @return true if actor is clickable
     */
    bool IsClickable() const { return mClickable; }

    /**
     * Actor clickable
     * @param clickable New clickable status
     */
    void SetClickable(bool clickable) { mClickable = clickable; }

    void SetPicture(Picture* picture);

    /**
     * Get the pointer to Picture
     * @return Picture pointer
     */
    Picture* GetPicture() { return mPicture; }

    void SetKeyframe();

    void GetKeyframe();

    AnimChannel* GetPositionChannel();

    void SetTimeline(Timeline * timeline);
};

#endif //CANADIANEXPERIENCE_ACTOR_H
