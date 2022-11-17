/**
 * @file RotatedBitmap.h
 * @author Ben Zuke
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ROTATEDBITMAP_H
#define CANADIANEXPERIENCE_ROTATEDBITMAP_H

/**
 * Create a rotated bitmap for sparty eyes and other bitmap eyes
 */
class RotatedBitmap
{
protected:
    /// The image for this drawable
    std::unique_ptr<wxImage> mImage;

    /// The graphics bitmap we will use
    wxGraphicsBitmap mBitmap;

    /// The center of the image
    wxPoint mCenter = wxPoint(0, 0);

    /// Has an image been loaded?
    bool mLoaded = false;

public:
    /// Constructor
    RotatedBitmap() {}

    /** Copy constructor disabled */
    RotatedBitmap(const RotatedBitmap&) = delete;

    /** Assignment operator disabled */
    void operator=(const RotatedBitmap&) = delete;

    /**
     * Set the center to rotate around
     * @param center New center
     */
    void SetCenter(wxPoint center) { mCenter = center; }

    void LoadImage(const std::wstring& filename);

    void DrawImage(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position, double angle);

    /**
     * Is this bitmap loaded for use?
     * @return true if loaded
     */
    bool IsLoaded() const { return mLoaded; }
};

#endif //CANADIANEXPERIENCE_ROTATEDBITMAP_H
