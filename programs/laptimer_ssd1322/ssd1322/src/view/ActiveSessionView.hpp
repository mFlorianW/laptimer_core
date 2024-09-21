// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef ACTIVESESSIONVIEW_HPP
#define ACTIVESESSIONVIEW_HPP

#include "ActiveSessionModel.hpp"
#include "MainScreenView.hpp"
#include "PopupRequest.hpp"
#include <lv_obj.h>

class ActiveSessionView : public MainScreenView
{
public:
    /**
     * Creates an instance of the ActiveSessionView
     * @param model The view model with the data and data updates.
     */
    ActiveSessionView(ActiveSessionModel& model);

    /**
     * Default desctructor cleans all UI elements.
     */
    ~ActiveSessionView() override;

    /**
     * Deleted copy Constructor
     */
    ActiveSessionView(ActiveSessionView const& view) = delete;

    /**
     * Deleted copy Assignment Constructor
     */
    ActiveSessionView& operator=(ActiveSessionView const& view) = delete;

    /**
     * Deleted move Constructor
     */
    ActiveSessionView(ActiveSessionView&& view);

    /**
     * Deleted move assignment operator
     */
    ActiveSessionView& operator=(ActiveSessionView&& view) = delete;

private:
    void onTrackDetected();
    void onTrackDetectionPopupClosed(PopupReturnType returnType);
    void onLapFinished();
    void onSectorFinshed();

private:
    // Laptime objects
    lv_style_t mLaptimeContainerStyle{};
    lv_obj_t* mLaptimeContainer{nullptr};
    lv_style_t mLaptimeLabelStyle{};
    lv_obj_t* mLaptimeLabel{nullptr};

    // Sector time objects
    lv_style_t mSectorTimeContainerStyle{};
    lv_obj_t* mSectorTimeContainer{nullptr};
    lv_style_t mSectorTimeLabelStyle{};
    lv_obj_t* mSectorTimeLabel{nullptr};

    // Lap objects
    lv_obj_t* mLapCountLabel{nullptr};

    // Popup Request
    PopupRequest mPopupRequest;
    PopupRequest mLaptimePopupRequest;

    // model
    ActiveSessionModel& mActiveSessionModel;
};

#endif //! ACTIVESESSIONVIEW_HPP
