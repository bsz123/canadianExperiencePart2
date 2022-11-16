/**
 * @file Drawable.h
 * @author Ben Zuke
 *
 * Abstract base class for drawable elements of our picture.
 */

#ifndef CANADIANEXPERIENCE_DRAWABLE_H
#define CANADIANEXPERIENCE_DRAWABLE_H

#include "AnimChannelAngle.h"

class Actor;
class Timeline;

/**
 * Abstract base class for drawable elements of our picture.
 *
 * A drawable is one part of an actor. Drawable parts can be moved
 * independently.
 */
class Drawable
{
private:
    /// The position relative to parent
    wxPoint mPosition = wxPoint(0,0);

    /// The drawable name
    std::wstring mName;

    /// Rotation relative to parent
    double mRotation = 0;

    /// The actor using this drawable
    Actor *mActor = nullptr;

    /// Drawables parent
    Drawable * mParent = nullptr;

    /// Drawables children
    std::vector<std::shared_ptr<Drawable>> mChildren;

    /// The animation channel for animating the angle of this drawable
    AnimChannelAngle mChannel;

protected:
    Drawable(const std::wstring &name);

    wxPoint RotatePoint(wxPoint point, double angle);

    /// Actual position Position
    wxPoint mPlacedPosition = wxPoint(0,0);

    /// Actual rotation
    double mPlacedR = 0;

public:
    /// Destructor
    virtual ~Drawable() {};

    /// Default constructor (disabled)
    Drawable() = delete;
    
    /// Copy constructor (disabled)
    Drawable(const Drawable &) = delete;
    
    /// Assignment operator
    void operator=(const Drawable &) = delete;

    void SetActor(Actor* actor);

    /**
     * Draw this drawable
     * @param graphics Graphics object to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    void Place(wxPoint offset, double rotate);

    void AddChild(std::shared_ptr<Drawable> child);

    /**
     * Test to see if we have been clicked on by the mouse
     * @param pos Position to test
     * @return true if clicked on
     */
    virtual bool HitTest(wxPoint pos) = 0;

    /**
     * Is this a movable drawable?
     * @return true if movable
     */
    virtual bool IsMovable() { return false; }

    void Move(wxPoint delta);

    /**
     * Set the drawable position
     * @param pos The new drawable position
     */
    void SetPosition(wxPoint pos) { mPosition = pos; }

    /**
     * Get the drawable position
     * @return The drawable position
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * Set the rotation angle in radians
    * @param r The new rotation angle in radians
     */
    void SetRotation(double r) { mRotation = r; }

    /**
     * Get the rotation angle in radians
     * @return The rotation angle in radians
     */
    double GetRotation() const { return mRotation; }

    /**
     * Get the drawable name
     * @return The drawable name
     */
    std::wstring GetName() const { return mName; }

    /**
     * Get the parent
     * @return The drawable parent
     */
    Drawable* GetParent() { return mParent; }

    /**
     * Set parent, called by add child
     * @param parent parent drawable
     */
    void SetParent( Drawable * parent) { mParent = parent; }

    virtual void SetTimeline(Timeline *timeline);

    /**
     * The angle animation channel
     * @return Pointer to animation channel
     */
    AnimChannelAngle *GetAngleChannel() { return &mChannel; }

    void SetKeyframe();

    void GetKeyframe();
};

#endif //CANADIANEXPERIENCE_DRAWABLE_H
