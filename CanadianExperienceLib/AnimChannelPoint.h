/**
 * @file AnimChannelMove.h
 * @author Ben Zuke
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELPOINT_H
#define CANADIANEXPERIENCE_ANIMCHANNELPOINT_H

#include "AnimChannel.h"

/**
 * Animation channel for points
 */
class AnimChannelPoint : public AnimChannel
{
private:
    wxPoint mPoint = wxPoint(0,0); ///< Channel Point

protected:
    class KeyframePoint : public Keyframe
    {
    private:
        wxPoint mPoint; ///< Keyframe Point

        AnimChannelPoint *mChannel; ///< Keyframe channel

    public:
        /**
         * Constructor
         * @param channel The channel we are for
         * @param point The point for the keyframe
         */
        KeyframePoint(AnimChannelPoint *channel, wxPoint point) :
              Keyframe(channel), mChannel(channel), mPoint(point) {}
        /// Default constructor (disabled)
        KeyframePoint() = delete;

        /// Copy constructor (disabled)
        KeyframePoint(const KeyframePoint &) = delete;

        /// Assignment operator
        void operator=(const KeyframePoint &) = delete;

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the Point
        void UseOnly() override { mChannel->mPoint = mPoint; }

        /// Point Getter
        wxPoint GetPoint() { return mPoint; }

    };

    void Tween(double t);

private:
    /// The first angle keyframe
    KeyframePoint *mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframePoint *mKeyframe2 = nullptr;

public:
    /// Default constructor
    AnimChannelPoint() {}

    /// Copy constructor (disabled)
    AnimChannelPoint(const AnimChannelPoint &) = delete;

    /// Assignment operator
    void operator=(const AnimChannelPoint &) = delete;

    wxPoint GetPoint() { return mPoint; }

    void SetKeyframe(wxPoint point);

};

#endif //CANADIANEXPERIENCE_ANIMCHANNELPOINT_H
