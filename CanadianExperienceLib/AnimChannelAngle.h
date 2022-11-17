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

    double mAngle = 0; ///< Current angle of channel


protected:

    /// Class that represents a keyframe
    class KeyframeAngle : public Keyframe
    {
    private:
        double mAngle; ///< Keyframe angle

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


        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the angle
        void UseOnly() override { mChannel->mAngle = mAngle; }

        /**
         * Angle getter
         * @return double representing angle
         */
        double GetAngle() { return mAngle; }

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

    /**
     * Angle Getter
     * @return Angle of object in double
     */
    double GetAngle() { return mAngle; }

    void SetKeyframe(double d);



};

#endif //CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
