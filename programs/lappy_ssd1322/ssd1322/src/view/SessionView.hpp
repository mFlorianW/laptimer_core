// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef SESSIONVIEW_HPP
#define SESSIONVIEW_HPP

#include "View.hpp"
#include <lv_obj.h>

class SessionViewModel;
class SessionView final : public View
{
public:
    SessionView(SessionViewModel& sessionViewModel);
    ~SessionView() override;

    // Delete copy constructor
    SessionView(SessionView const&) = delete;

    // Delete copy assignment operator
    SessionView& operator=(SessionView const&) = delete;

    // Delete move constructor
    SessionView(SessionView&&) = delete;

    // Delete move assignment operator
    SessionView& operator=(SessionView&&) = delete;

    void handleButtonDown() override;

    void handleButtonUp() override;

    void handleEnter() override;

private:
    void setTrackName();
    void setDate();
    void setTime();
    void setLaps();
    void setBestLap();
    void setSessionIndicator();

private:
    lv_style_t mLabelStyle{};
    lv_obj_t* mSessionLabel;
    lv_obj_t* mSessionIndicatorLabel;
    lv_obj_t* mTrackNameLabel;
    lv_obj_t* mDateLabel;
    lv_obj_t* mLapLabel;
    lv_obj_t* mTimeLabel;
    lv_obj_t* mBestLapLabel;
    SessionViewModel& mSessionViewModel;
};

#endif // SESSIONVIEW_HPP
