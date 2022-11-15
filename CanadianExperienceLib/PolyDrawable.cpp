/**
 * @file PolyDrawable.cpp
 * @author Ben Zuke
 */

#include "pch.h"
#include "PolyDrawable.h"

/**
 * Constructor
 * @param name The drawable name
 */
PolyDrawable::PolyDrawable(const std::wstring& name) : Drawable(name)
{

}

/**
 * Draw the poly
 * @param graphics Graphics context
 */
void PolyDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(!mPoints.empty()) {

        mPath = graphics->CreatePath();
        mPath.MoveToPoint(RotatePoint(mPoints[0], mPlacedR) + mPlacedPosition);
        for (auto i = 1; i<mPoints.size(); i++)
        {
            mPath.AddLineToPoint(RotatePoint(mPoints[i], mPlacedR) + mPlacedPosition);
        }
        mPath.CloseSubpath();

        wxBrush brush(mColor);
        graphics->SetBrush(brush);
        graphics->FillPath(mPath);
    }
}

/**
 * Test for mouse click
 * @param point Tested point
 * @return boolean if object hit
 */
bool PolyDrawable::HitTest(wxPoint point)
{
    return mPath.Contains(point.x, point.y);
}

/**
 * Add a point to our polygon
 * @param point point coordinates
 */
void PolyDrawable::AddPoint(wxPoint point)
{
    mPoints.push_back(point);
}
