/**
 * @file AnimChannel.h
 * @author Ben Zuke
 *
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNEL_H
#define CANADIANEXPERIENCE_ANIMCHANNEL_H

#include "Timeline.h"

/**
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class AnimChannel
{
private:

    std::wstring mName; ///< Channel Name

    int mKeyframe1 = -1; ///< Left Keyframe
    int mKeyframe2 = -1; ///< Right Keyframe

    /// The timeline object
    Timeline *mTimeline = nullptr;


protected:


    /// Class that represents a keyframe
    class Keyframe
    {
    private:
        /// The channel this keyframe is associated with
        AnimChannel *mChannel;

    protected:
        int mFrame; ///< Current keyframe indice

        /**
         * Constructor
         * @param channel Channel we are associated with
         */
        Keyframe(AnimChannel *channel) : mChannel(channel) {}

    public:

        /**
         * Constructor
         * @param channel Current channel
         */
        Keyframe( AnimChannel channel )
        {

        }

        /// Pure virtual keyframe1
        virtual void UseAs1() = 0;

        /// Pure virtual keyframe2
        virtual void UseAs2() = 0;

        /// Pure virtual keyframe only
        virtual void UseOnly() = 0;

        /// Default constructor (disabled)
        Keyframe() = delete;

        /// Copy constructor (disabled)
        Keyframe(const Keyframe &) = delete;

        /// Assignment operator
        void operator=(const Keyframe &) = delete;

        /**
         * Frame setter
         * @param curr indice of current frame
         */
        void SetFrame(int curr) { mFrame = curr; }

        /**
         * Frame Getter
         * @return current frame
         */
        int GetFrame() { return mFrame; }

    };

    void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

    virtual void Tween(double t);

private:
    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;

public:

    /// Default constructor
    AnimChannel() { }

    /// Copy constructor (disabled)
    AnimChannel(const AnimChannel &) = delete;

    /// Assignment operator
    void operator=(const AnimChannel &) = delete;

    /**
     * Name Setter
     * @param name name of our channel
     */
    void SetName(std::wstring name) { mName = name; }

    /**
     * Name Getter
     * @return string of our channel name
     */
    std::wstring GetName() { return mName; }

    bool IsValid();

    void SetFrame(int currFrame);

    /**
     * Timeline Setter
     * @param timeline pointer
     */
    void SetTimeline(Timeline * timeline) { mTimeline = timeline; }

    /**
     * Timeline Getter
     * @return timeline our channel is associated with
     */
    Timeline* GetTimeline() { return mTimeline; }

    void DeleteFrame();
};

#endif //CANADIANEXPERIENCE_ANIMCHANNEL_H
