/**
 * @file HeadTop.cpp
 * @author Ben Zuke
 */

#include "HeadTop.h"
#include "ImageDrawable.h"



/**
 * HeadTop constructor
 * @param name HeadTop name
 * @param filename the file for headtop
 */
HeadTop::HeadTop(const std::wstring& name, const std::wstring& filename)
        :ImageDrawable(name, filename)
{

}

/**
 * Draw the head and it's facial expressions
 * @param graphics
 */
void HeadTop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    ImageDrawable::Draw(graphics);

    // Distance horizontally from each eye center to the center
    int d2 = mInterocularDistance / 2;

    // Compute a left and right eye center X location
    int rightX = mEyesCenter.x - d2;
    int leftX = mEyesCenter.x + d2;

    // Eye center Y value
    int eyeY = mEyesCenter.y;

    if (mLeftEye.IsLoaded() && mRightEye.IsLoaded())
    {
        // Determine the point on the screen were we will draw the left eye
        wxPoint leye = TransformPoint(wxPoint(leftX, eyeY));
        // And draw the bitmap there
        mLeftEye.DrawImage(graphics, leye, mPlacedR);

        // Repeat the process for the right eye.
        wxPoint reye = TransformPoint(wxPoint(rightX, eyeY));
        mRightEye.DrawImage(graphics, reye, mPlacedR);
    }
    else
    {
        DrawEyebrow(graphics, wxPoint(rightX - 10, eyeY - 16), wxPoint(rightX + 4, eyeY - 18));
        DrawEyebrow(graphics, wxPoint(leftX - 4, eyeY - 20), wxPoint(leftX + 9, eyeY - 18));

        DrawEye(graphics, wxPoint(leftX, eyeY));
        DrawEye(graphics, wxPoint(rightX, eyeY));
    }


    ImageDrawable::Draw(graphics);

    SetEyeHit(GetImageHeight());

    Eyebrow(graphics, true);
    Eyebrow(graphics, false);

    float wid = 15.0f;
    float hit = 20.0f;

    wxPoint e1 = TransformPoint(wxPoint(40, mEyeHit));
    wxPoint e2 = TransformPoint(wxPoint(70, mEyeHit));

    graphics->PushState();
    graphics->SetBrush(*wxBLACK);
    graphics->Translate(e1.x, e1.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();

    graphics->PushState();
    graphics->Translate(e2.x, e2.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();

}

/**
 * Draw an eyebrow, automatically transforming the points
 *
 * Draw a line from (x1, y1) to (x2, y2) after transformation
 * to the local coordinate system.
 * @param graphics Graphics context to draw on
 * @param p1 First point
 * @param p2 Second point
 */
void HeadTop::DrawEyebrow(std::shared_ptr<wxGraphicsContext> graphics,
        wxPoint p1, wxPoint p2)
{
    auto eb1 = TransformPoint(p1);
    auto eb2 = TransformPoint(p2);

    wxPen eyebrowPen(*wxBLACK, 2);
    graphics->SetPen(eyebrowPen);
    graphics->StrokeLine(eb1.x, eb1.y, eb2.x, eb2.y);
}

/**
 * Draw the eyebrows for harold
 * @param graphics Graphics context
 * @param left if eyebrow is left or right
 */
void HeadTop::Eyebrow(std::shared_ptr<wxGraphicsContext> graphics, bool left)
{
    float browWid = 14.0f;
    float browHit = 2.0f;
    graphics->PushState();
    wxPoint p;
    if (left)
    {
        browWid *= -1;
        p =  TransformPoint(wxPoint(46, mEyebrowHit));
    }
    else{ p = TransformPoint(wxPoint(63, mEyebrowHit));}

    graphics->Translate(p.x, p.y);

    graphics->SetPen(*wxBLACK_PEN);
    graphics->Rotate(-mPlacedR);
    graphics->StrokeLine(0, 0, browWid, browHit);

    graphics->PopState();

}

/**
 * Draw an eye using an Ellipse
 * @param graphics The graphics context to draw on
 * @param p1 Where to draw before transformation */
void HeadTop::DrawEye(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p1)
{
    graphics->SetBrush(*wxBLACK_BRUSH);
    graphics->SetPen(*wxTRANSPARENT_PEN);

    auto e1 = TransformPoint(p1);

    float wid = 15.0f;
    float hit = 20.0f;

    graphics->PushState();
    graphics->Translate(e1.x, e1.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();
}

/**
 * Override base class IsMoveable
 * @return that head is movable
 */
bool HeadTop::IsMovable()
{
    return true;
}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* @param  p Point to transform
* @returns Transformed point
*/
wxPoint HeadTop::TransformPoint(wxPoint p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}

/**
 * Eyebrow and Eye height setter
 * @param hit Height of image
 */
void HeadTop::SetEyeHit(float hit)
{
    mEyeHit = hit * .7;
    mEyebrowHit = mEyeHit-19;
}

void HeadTop::SetInterocularDistance(float dis)
{
    mInterocularDistance = dis;
}
