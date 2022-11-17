/**
 * @file TimelineDlg.h
 * @author Ben Zuke
 *
 *
 */

#ifndef CANADIANEXPERIENCE_TIMELINEDLG_H
#define CANADIANEXPERIENCE_TIMELINEDLG_H

#include "Timeline.h"

/**
 * Timeline dialog box
 */
class TimelineDlg final : public wxDialog
{
private:

    Timeline* mTimeline; ///< Timeline pointer

    /// Number of frames in the animation
    int mNumberOfFrames;

    int mFrameRate; ///< Pointer of timeline framerate

public:

    TimelineDlg(wxWindow* parent, Timeline* timeline);

    void OnOK(wxCommandEvent& event);
};

#endif //CANADIANEXPERIENCE_TIMELINEDLG_H
