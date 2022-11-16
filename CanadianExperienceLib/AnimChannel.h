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

/**
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class AnimChannel
{
private:

    std::wstring mName;

    int keyframe1 = -1;
    int keyframe2 = -1;

protected:


    /// Class that represents a keyframe
    class Keyframe
    {
    private:

    protected:
        int mFrame;

    public:

        Keyframe( AnimChannel channel )
        {

        }

        void UseAs1();

        void UseAs2();

        void UseOnly();

    };

    /**
     * Insert a keyframe to our AnimChannel
     * @param keyframe
     */
    void InsertKeyframe(std::shared_ptr<Keyframe> keyframe)
    {

    }

    virtual void Tween(double t);

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


};

#endif //CANADIANEXPERIENCE_ANIMCHANNEL_H
