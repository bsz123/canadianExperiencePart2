/**
 * @file Timeline.cpp
 * @author Ben Zuke
 */

#include "pch.h"
#include "Timeline.h"

#include "AnimChannel.h"


/**
 * Constructor
 */
Timeline::Timeline()
{

}

/**
 * Get the animation duration
 * @return Animation duration in seconds
 */
double Timeline::GetDuration() const
{
    return double(mNumFrames)/double(mFrameRate);
}

/** Get the current frame.
 *
 * This is the frame associated with the current time
 * @return Current frame
 */
int Timeline::GetCurrentFrame() const
{
    return int(mCurrentTime * mFrameRate);
}

/**
 * Delete the current keyframe
 * find any channel matching time
 */
void Timeline::DeleteKeyframe()
{
    for (auto channel : mChannels)
    {
        channel->DeleteFrame();
    }

}

/**
 * Add a channel to timeline
 *
 * @param channel
 */
void Timeline::AddChannel(AnimChannel *channel)
{
    mChannels.push_back(channel);
    channel->SetTimeline(this);
}

/**
 * Sets the current time
 *
 * Ensures all of the channels are
 * valid for that point in time.
 * @param t The new time to set
 */
void Timeline::SetCurrentTime(double t)
{
    // Set the time
    mCurrentTime = t;

    for (auto channel : mChannels)
    {
        channel->SetFrame(GetCurrentFrame());
    }
}
