/**
 * @file HeadTop.h
 * @author Ben Zuke
 *
 * The specialization of Head top
 */

#ifndef CANADIANEXPERIENCE_HEADTOP_H
#define CANADIANEXPERIENCE_HEADTOP_H

#include "ImageDrawable.h"


/**
 * Class that specializes the head top
 */
class HeadTop : public ImageDrawable
{
private:
    /// The height we start drawing eyebrows from
    float mEyebrowHit;

    /// The height we draw the eyes around
    float mEyeHit;

    RotatedBitmap mLeftEye;        ///< Bitmap for the left eye
    RotatedBitmap mRightEye;       ///< Bitmap for the right eye

    wxPoint mEyesCenter; ///< Center of eyes
    float mInterocularDistance; ///< Distance between eyes
    float mEyeLeft; ///< Left ellipse
    float mEyeRight; ///< Right ellipse

    AnimChannelPoint mChannelP; ///< Animation channel point
    AnimChannelAngle mChannelA; ///< Animation channel angle

public:
    
    HeadTop(const std::wstring& name, const std::wstring& filename);

    /// Default constructor (disabled)
    HeadTop() = delete;
    
    /// Copy constructor (disabled)
    HeadTop(const HeadTop &) = delete;
    
    /// Assignment operator
    void operator=(const HeadTop &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool IsMovable() override;

    wxPoint TransformPoint(wxPoint p);

    void Eyebrow(std::shared_ptr<wxGraphicsContext> graphics, bool left);

    void SetEyeHit(float hit);

    /**
     * Get a pointer to the left eye bitmap
     * @return Pointers to the left eye bitmap
     */
    RotatedBitmap *GetLeftEye() {return &mLeftEye;}

    /**
     * Get a pointer to the left eye bitmap
     * @return Pointers to the left eye bitmap
     */
    RotatedBitmap *GetRightEye() {return &mRightEye;}

    /**
     * Set the center of eyes
     * @param center Point that is the middle of the image
     */
     void SetEyesCenter(wxPoint point) { mEyesCenter = point; }

    void DrawEyebrow(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p1, wxPoint p2);

    void DrawEye(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p1);

    void SetInterocularDistance(float dis);

    void SetEyeX(float left, float right);

    void SetKeyframe(); // if override crash

    void GetKeyframe();
};

#endif //CANADIANEXPERIENCE_HEADTOP_H
