/**
 * @file Actor.cpp
 * @author Ben Zuke
 *
 */

#include "pch.h"

#include <memory>

#include "Actor.h"
#include "Drawable.h"
#include "Picture.h"

/**
 * Constructor
 * @param name the actor name
 */
Actor::Actor(const std::wstring& name) : mName(name)
{

}

/**
 * Set the root drawable for the actor
 * @param root Pointer to root drawable
 */
void Actor::SetRoot(std::shared_ptr<Drawable> root)
{
    mRoot = root;
}

/**
 * Draws the actor
 * @param graphics The Graphics context we draw on
 */
void Actor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Don't draw if not enabled
    if (!mEnabled)
        return;

    // This takes care of determining the absolute placement
    // of all of the child drawables. We have to determine this
    // in tree order, which may not be the order we draw.
    if (mRoot != nullptr)
        mRoot->Place(mPosition, 0);

    for (auto drawable : mDrawablesInOrder)
    {
        drawable->Draw(graphics);
    }
}

/**
 * Test to see if this actor was clicked
 * @param pos Mouse pos
 * @return drawble object or nullptr
 */
std::shared_ptr<Drawable> Actor::HitTest(wxPoint pos)
{
    // If not enabled or not clickable, we indicate no hit.
    if (!mClickable || !mEnabled)
        return nullptr;

    // Since this list is in drawing order, we realy want to know the last thing drawn
    // under the mouse, since it will be on top. So, we reverse iterate over the list.
    for (auto d = mDrawablesInOrder.rbegin(); d != mDrawablesInOrder.rend(); d++)
    {
        auto drawable = *d;
        if (drawable->HitTest(pos))
            return drawable;
    }

    return nullptr;
}

/**
* Add a drawable to this actor
* @param drawable The drawable to add
*/
void Actor::AddDrawable(std::shared_ptr<Drawable> drawable)
{
    mDrawablesInOrder.push_back(drawable);
    drawable->SetActor(this);
}

/**
 * Set the picture link for this actor.
 *
 * This is telling the actor what
 * picture to use.
 *
 * Also tells all child drawables what the timeline is.
 * @param picture The picture we are using.
 */
void Actor::SetPicture(Picture *picture)
{
    mPicture = picture;

    mPicture->GetTimeline()->AddChannel(&mAnimChannel);
    // Set the timeline for all drawables. This links the channels to
    // the timeline system.
    for (auto drawable : mDrawablesInOrder)
    {
        drawable->SetTimeline(mPicture->GetTimeline());
    }

}

/**
 * Set a keyframe on an actor.
 */
void Actor::SetKeyframe()
{
    mAnimChannel.SetKeyframe(mPosition);
    for (auto drawable : mDrawablesInOrder)
    {
        drawable->SetKeyframe();
    }

}

/**
 * Get a keyframe for an actor.
 */
void Actor::GetKeyframe()
{
    if(mAnimChannel.IsValid())
    {
        mPosition = mAnimChannel.GetPoint();
    }
    for (auto drawable : mDrawablesInOrder)
    {
        drawable->GetKeyframe();
    }

}

/**
 * Return the channel for ps
 * @return pointer to the AnimChannel
 */
AnimChannel* Actor::GetPositionChannel()
{
    return &mAnimChannel;
}


