/**
 * @file AnimChannelAngle.h
 * @author Ben Zuke
 *
 * Animation channel for angles.
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
#define CANADIANEXPERIENCE_ANIMCHANNELANGLE_H

#include "AnimChannel.h"

/**
* Animation channel for angles.
*/
class AnimChannelAngle : public AnimChannel
{
private:

    double mAngle = 0;


protected:



    /// Class that represents a keyframe
    class KeyframeAngle : public Keyframe
    {
    private:
        double mAngle;

        /// The channel this keyframe is associated with
        AnimChannelAngle *mChannel;

    protected:

    public:
        /**
         * Constructor
         * @param channel The channel we are for
         * @param angle The angle for the keyframe
         */
        KeyframeAngle(AnimChannelAngle *channel, double angle) :
                Keyframe(channel), mChannel(channel), mAngle(angle) {}
                
        /// Default constructor (disabled)
        KeyframeAngle() = delete;
        
        /// Copy constructor (disabled)
        KeyframeAngle(const KeyframeAngle &) = delete;
        
        /// Assignment operator
        void operator=(const KeyframeAngle &) = delete;

        
        void UseAs1();

        void UseAs2();

        void UseOnly();

    };

    void Tween(double t);

private:
    /// The first angle keyframe
    KeyframeAngle *mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframeAngle *mKeyframe2 = nullptr;

public:
    /// Default constructor
    AnimChannelAngle() { }

    /// Copy constructor (disabled)
    AnimChannelAngle(const AnimChannelAngle &) = delete;

    /// Assignment operator
    void operator=(const AnimChannelAngle &) = delete;

    double GetAngle() { return mAngle; }

};

#endif //CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
