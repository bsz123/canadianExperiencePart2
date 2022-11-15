/**
 * @file PolyDrawable.h
 * @author Ben Zuke
 *
 * A drawable based on polygon images.
 */

#ifndef CANADIANEXPERIENCE_POLYDRAWABLE_H
#define CANADIANEXPERIENCE_POLYDRAWABLE_H

#include "Drawable.h"

/**
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
class PolyDrawable : public Drawable
{
private:
    /// The polygon color
    wxColour mColor = *wxBLACK;

    /// The array of point objects
    std::vector<wxPoint> mPoints;

    /// The transformed graphics path used
    /// to draw this polygon
    wxGraphicsPath mPath;

public:
    /// Default constructor (disabled)
    PolyDrawable() = delete;

    /// Copy constructor (disabled)
    PolyDrawable(const PolyDrawable &) = delete;

    /// Assignment operator
    void operator=(const PolyDrawable &) = delete;

    /**
     * Color Getter
     * @return the color
     */
    wxColour GetColor() { return mColor; }

    /**
     * Color setter
     * @param color the wxColour we want set
     */
    void SetColor(wxColour color) { mColor = color; }

    PolyDrawable(const std::wstring &name);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    bool HitTest(wxPoint point);

    void AddPoint(wxPoint point);

};

#endif //CANADIANEXPERIENCE_POLYDRAWABLE_H
