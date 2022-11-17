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

    std::wstring mName;

    int mKeyframe1 = -1;
    int mKeyframe2 = -1;

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
        int mFrame;

        /**
         * Constructor
         * @param channel Channel we are associated with
         */
        Keyframe(AnimChannel *channel) : mChannel(channel) {}

    public:

        Keyframe( AnimChannel channel )
        {

        }

        virtual void UseAs1() = 0;

        virtual void UseAs2() = 0;

        virtual void UseOnly() = 0;

        /// Default constructor (disabled)
        Keyframe() = delete;

        /// Copy constructor (disabled)
        Keyframe(const Keyframe &) = delete;

        /// Assignment operator
        void operator=(const Keyframe &) = delete;

        void SetFrame(int curr) { mFrame = curr; }

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

    /// Name Setter
    void SetName(std::wstring name) { mName = name; }

    /// Name Getter
    std::wstring GetName() { return mName; }

    bool IsValid();

    void SetFrame(int currFrame);

    void SetTimeline(Timeline * timeline) { mTimeline = timeline; }

    Timeline* GetTimeline() { return mTimeline; }


};

#endif //CANADIANEXPERIENCE_ANIMCHANNEL_H
