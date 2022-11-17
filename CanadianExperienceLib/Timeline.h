/**
 * @file Timeline.h
 * @author Ben Zuke
 *
 * This class implements a timeline that manages the animation
 *
 * A timeline consists of animation channels for different parts of our
 * actors, each with keyframes that set the position, orientation, etc
 * at that point in time.
 */

#ifndef CANADIANEXPERIENCE_TIMELINE_H
#define CANADIANEXPERIENCE_TIMELINE_H

class AnimChannel;

/**
 * A timeline consists of animation channels for different parts of our
 * actors, each with keyframes that set the position, orientation, etc
 * at that point in time.
 */
class Timeline
{
private:

    int mNumFrames = 300;
    int mFrameRate = 30;

    double mCurrentTime = 0;

    /// List of all animation channels
    std::vector<AnimChannel *> mChannels;

public:

    /// Empty constructor
    Timeline();

    /// Copy constructor (disabled)
    Timeline(const Timeline &) = delete;

    /// Assignment operator
    void operator=(const Timeline &) = delete;
    /**
     * Get the number of frames in the animation
     * @return Number of frames in the animation
     */
    int GetNumFrames() const {return mNumFrames;}

    /**
     * Set the number of frames in the animation
     * @param numFrames Number of frames in the animation
     */
    void SetNumFrames(int numFrames) {mNumFrames = numFrames;}

    /**
     * Get the frame rate
     * @return Animation frame rate in frames per second
     */
    int GetFrameRate() const {return mFrameRate;}

    /**
     * Set the frame rate
     * @param frameRate Animation frame rate in frames per second
     */
    void SetFrameRate(int frameRate) {mFrameRate = frameRate;}

    /**
     * Get the current time
     * @return Current animation time in seconds
     */
    double GetCurrentTime() const {return mCurrentTime;}

    void SetCurrentTime(double currentTime);

    double GetDuration() const;

    int GetCurrentFrame() const;

    void AddChannel(AnimChannel *channel);

    void DeleteKeyframe();
};

#endif //CANADIANEXPERIENCE_TIMELINE_H
