/**
 * @file AnimChannelPoint.cpp
 * @author Ben Zuke
 */

#include "AnimChannelPoint.h"

void AnimChannelPoint::SetKeyframe(wxPoint point)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the point
    std::shared_ptr<Keyframe> keyframe = std::make_shared<KeyframePoint>(this, point);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}

void AnimChannelPoint::Tween(double t)
{
    wxPoint a = mKeyframe1->GetPoint();
    wxPoint b = mKeyframe2->GetPoint();
    //double t = 0.3;

    wxPoint c = wxPoint(int(a.x + t * (b.x - a.x)),
            int(a.y + t * (b.y - a.y)));
    //mPoint = wxPoint(int(mKeyframe1->GetPoint().x + t *)
    mPoint = c;
}
