/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>

#include "ViewTimeline.h"
#include "TimelineDlg.h"
#include "Picture.h"

/**
 * Constructor
 * @param parent The main wxFrame object
 */
ViewTimeline::ViewTimeline(wxFrame* parent) :
    wxWindow(parent,
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
}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    wxPen pen(wxColour(0, 128, 0), 1);
    graphics->SetPen(pen);
    graphics->DrawRectangle(10, 10, 200, 60);

    wxFont font(wxSize(0, 16),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);
    graphics->DrawText(L"Timeline!", 15, 15);

    auto time = wxDateTime::Now();
    auto timeStr = time.Format(L"%x %T");
    graphics->DrawText(timeStr, 15, 40);

}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent &event)
{

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

}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
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
