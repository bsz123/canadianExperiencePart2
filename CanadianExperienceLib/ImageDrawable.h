/**
 * @file ImageDrawable.h
 * @author Ben Zuke
 *
 * Class that attaches image to drawable
 */

#ifndef CANADIANEXPERIENCE_IMAGEDRAWABLE_H
#define CANADIANEXPERIENCE_IMAGEDRAWABLE_H

#include "Drawable.h"
#include "RotatedBitmap.h"

/**
 * Attach images to drawable objects
 */
class ImageDrawable : public Drawable, public RotatedBitmap
{
private:

public:

    ImageDrawable(const std::wstring& name, const std::wstring& filename);

    /// Default constructor (disabled)
    ImageDrawable() = delete;
    
    /// Copy constructor (disabled)
    ImageDrawable(const ImageDrawable &) = delete;

    /// Assignment operator
    void operator=(const ImageDrawable &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    bool HitTest(wxPoint pos);

    /**
     * Center Getter
     * @return Center of image
     */
    wxPoint GetCenter() { return mCenter; }

    /**
     * Image height getter
     * @return Height of bitmap
     */
    float GetImageHeight() { return mImage->GetHeight(); }

};

#endif //CANADIANEXPERIENCE_IMAGEDRAWABLE_H
