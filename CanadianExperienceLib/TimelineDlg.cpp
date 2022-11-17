/**
 * @file TimelineDlg.cpp
 * @author Ben Zuke
 */

#include "pch.h"

#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>
#include "TimelineDlg.h"

/**
 * Constructor for dialog
 * @param parent
 * @param timeline
 */
TimelineDlg::TimelineDlg(wxWindow* parent, Timeline* timeline)
    : mTimeline(timeline)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"TimelineDlg");
    mNumberOfFrames = timeline->GetNumFrames();
    mFrameRate = timeline->GetFrameRate();

    auto numFramesCtrl = XRCCTRL(*this, "TimelineDlgNumFrames", wxTextCtrl);
    auto frameRateCtrl = XRCCTRL(*this, "TimelineDlgFrameRate", wxTextCtrl);

    wxIntegerValidator<int> numFramesValidator(&mNumberOfFrames);
    numFramesValidator.SetRange(1, 10000);
    numFramesCtrl->SetValidator(numFramesValidator);

    wxIntegerValidator<int> frameRateValidator(&mFrameRate);
    frameRateValidator.SetRange(1, 10000);
    frameRateCtrl->SetValidator(frameRateValidator);

    Bind(wxEVT_BUTTON, &TimelineDlg::OnOK, this, wxID_OK);
}

/**
 * Handle an OK button press
 * @param event Button event
 */
void TimelineDlg::OnOK(wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        // Success! Set values in the class
        mTimeline->SetNumFrames(mNumberOfFrames);

        EndModal(wxID_OK);
    }

}
