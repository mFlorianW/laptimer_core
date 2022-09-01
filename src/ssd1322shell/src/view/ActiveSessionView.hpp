#ifndef __ACTIVESESSIONVIEW__H__
#define __ACTIVESESSIONVIEW__H__

#include "ActiveSessionModel.hpp"
#include "MainScreenView.hpp"
#include "PopupRequest.hpp"
#include <lv_obj.h>

class ActiveSessionView : public MainScreenView
{
public:
    ActiveSessionView(ActiveSessionModel &model);

    ~ActiveSessionView();

private:
    void onTrackDetected();
    void onTrackDetectionPopupClosed(PopupReturnType returnType);

private:
    // Laptime objects
    lv_style_t mLaptimeContainerStyle;
    lv_obj_t *mLaptimeContainer;
    lv_style_t mLaptimeLabelStyle;
    lv_obj_t *mLaptimeLabel;

    // Sector time objects
    lv_style_t mSectorTimeContainerStyle;
    lv_obj_t *mSectorTimeContainer;
    lv_style_t mSectorTimeLabelStyle;
    lv_obj_t *mSectorTimeLabel;

    // Lap objects
    lv_obj_t *mLapCountLabel;

    // Popup Request
    PopupRequest mPopupRequest;

    // model
    ActiveSessionModel &mActiveSessionModel;
};

#endif //!__ACTIVESESSIONVIEW__H__