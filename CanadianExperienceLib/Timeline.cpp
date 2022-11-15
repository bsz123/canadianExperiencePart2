/**
 * @file Timeline.cpp
 * @author Ben Zuke
 */

#include "pch.h"
#include "Timeline.h"


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
