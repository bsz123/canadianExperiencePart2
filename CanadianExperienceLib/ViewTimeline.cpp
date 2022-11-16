/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 * @author Ben Zuke
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>
#include <sstream>

#include "ViewTimeline.h"
#include "TimelineDlg.h"
#include "Picture.h"
#include "Actor.h"

using namespace std;

/// Y location for the top of a tick mark
const int TickTop = 15;

/// The spacing between ticks in the timeline
const int TickSpacing = 4;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// Size of the tick mark labels
const int TickFontSize = 15;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;

/// Filename for the pointer image
const std::wstring PointerImageFile = L"/pointer.png";

/**
 * Constructor
 * @param parent The main wxFrame object
 */
ViewTimeline::ViewTimeline(wxFrame* parent, std::wstring img) :
    wxScrolledCanvas(parent,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(100, Height),
            wxBORDER_SIMPLE)
{


    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ViewTimeline::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewTimeline::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewTimeline::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewTimeline::OnMouseMove, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ViewTimeline::OnEditTimelineProperties, this,
            XRCID("EditTimelineProperties"));
    mPointerImage = make_unique<wxImage>(img + PointerImageFile, wxBITMAP_TYPE_ANY);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnSetKeyframe,
            this, XRCID("SetKeyframe"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnDeleteKey,
            this, XRCID("DeleteKeyframe"));
}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    Timeline* timeline = GetPicture()->GetTimeline();
    double tickNum = timeline->GetNumFrames();

    // Total Frames * tick spacing + left border + right boarder, member height
    SetVirtualSize(tickNum * TickSpacing + BorderLeft + BorderRight, Height);
    SetScrollRate(1, 0);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    wxPen pen(wxColour(0, 128, 0), 1);
    graphics->SetPen(pen);

    wxFont font(wxSize(0, 16),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);

    double leftPad = BorderLeft;
    bool onSecond;

    int frameRate = timeline->GetFrameRate();

    for (int tick = 0; tick <= tickNum; tick++)
    {
        onSecond = (int(tick) % frameRate) == 0;

        if (onSecond)
        {
            // Convert the tick number to seconds in a string
            graphics->StrokeLine(leftPad, TickTop, leftPad, TickTop+TickLong);
            std::wstringstream str;
            str << tick/frameRate;
            std::wstring wstr = str.str();

            double w, h;
            graphics->GetTextExtent(wstr, &w, &h);
            graphics->DrawText(wstr, leftPad-(w/2), TickTop+TickLong);
        }
        else
        {
            graphics->StrokeLine(leftPad, TickTop, leftPad, TickTop+TickShort);
        }
        leftPad += TickSpacing;
    }
    if (mPointerBitmap.IsNull())
    {
        mPointerBitmap = graphics->CreateBitmapFromImage(*mPointerImage);
    }


    graphics->DrawBitmap(mPointerBitmap,
            timeline->GetCurrentTime()*frameRate*TickSpacing+BorderLeft/2, 10,
            mPointerImage->GetWidth(),
            mPointerImage->GetHeight());


}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    int x = click.x;

    // Get the timeline
    Timeline *timeline = GetPicture()->GetTimeline();
    int pointerX = (int)(timeline->GetCurrentTime() *
            timeline->GetFrameRate() * TickSpacing + BorderLeft);

    mMovingPointer = x >= pointerX - mPointerImage->GetWidth() / 2 &&
            x <= pointerX + mPointerImage->GetWidth() / 2;

}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewTimeline::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void ViewTimeline::OnMouseMove(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    Timeline* timeline = GetPicture()->GetTimeline();

    if(mMovingPointer)
    {
        if (event.LeftIsDown())
        {
            // time = (pointx-left)/(FrameRate*TickSpace)
            double animateTime = (click.x - BorderLeft)/
                    (double(timeline->GetFrameRate())*TickSpacing);
            GetPicture()->SetAnimationTime(animateTime);
        }
    }
}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
    Update();
}

/**
 * Handle an Edit>Timeline Properties... menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditTimelineProperties(wxCommandEvent& event)
{
    TimelineDlg dlg(this->GetParent(), GetPicture()->GetTimeline());
    if(dlg.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the Timeline settings
        GetPicture()->UpdateObservers();
    }
}

/**
 * Keyframe setter event handler
 * @param event
 */
void ViewTimeline::OnSetKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->SetKeyframe();
    }
}

/**
 * Delete keyframe event handler
 * @param event
 */
void ViewTimeline::OnDeleteKey(wxCommandEvent& event)
{
    int x = 0;
}
