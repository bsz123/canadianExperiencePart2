/**
 * @file AnimChannelPoint.cpp
 * @author Ben Zuke
 */

#include "pch.h"
#include "AnimChannelPoint.h"

/**
 * Keyframe Setter
 * @param point wxPoint our object is located
 */
void AnimChannelPoint::SetKeyframe(wxPoint point)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the point
    std::shared_ptr<KeyframePoint> keyframe = std::make_shared<KeyframePoint>(this, point);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}

/**
 * Tween the animation, using math provided
 * @param t
 */
void AnimChannelPoint::Tween(double t)
{
    wxPoint a = mKeyframe1->GetPoint();
    wxPoint b = mKeyframe2->GetPoint();

    wxPoint c = wxPoint(int(a.x + t * (b.x - a.x)),
            int(a.y + t * (b.y - a.y)));

    mPoint = c;
}
