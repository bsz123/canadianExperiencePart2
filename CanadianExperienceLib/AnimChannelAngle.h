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
    class KeyframeAngle
    {
    private:

    protected:
        double mAngle;

    public:
        KeyframeAngle()
        {

        }

        void UseAs1();

        void UseAs2();

        void UseOnly();

    };

    void Tween(double t);

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
