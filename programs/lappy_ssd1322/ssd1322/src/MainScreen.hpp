// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "Screen.hpp"
#include "StatusBarModel.hpp"
#include "View.hpp"

class MainScreen : public Screen
{
public:
    explicit MainScreen(LaptimerCore::Positioning::IGpsInformationProvider& gpsInfoProvider);
    ~MainScreen() override;

    // Delete copy constructor
    MainScreen(MainScreen const&) = delete;

    // Delete copy assignment operator
    MainScreen& operator=(MainScreen const&) = delete;

    // Delete move constructor
    MainScreen(MainScreen&&) = delete;

    // Delete move assignment operator
    MainScreen& operator=(MainScreen&&) = delete;

private:
    void onNumberOfSatelliteChanged();

private:
    // indication bar container
    lv_style_t mMainScreenContainerStyle{};
    lv_obj_t* mIndicationBarContainer;
    lv_obj_t* mSatelliteLabel;

    // main screen separator
    lv_point_t mSeparatorPoints[2]{{0, 15}, {256, 15}}; // NOLINT(modernize-avoid-c-arrays)
    lv_style_t mSeparatorStyle{};
    lv_obj_t* m_separator_line;

    StatusBarModel mStatusBarModel;
};
