// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "Screen.hpp"
#include <lvgl.h>

class MenuScreen : public Screen
{
public:
    MenuScreen();
    ~MenuScreen() override;

    // Delete copy constructor
    MenuScreen(MenuScreen const&) = delete;

    // Delete copy assignment operator
    MenuScreen& operator=(MenuScreen const&) = delete;

    // Delete move constructor
    MenuScreen(MenuScreen&&) = delete;

    // Delete move assignment operator
    MenuScreen& operator=(MenuScreen&&) = delete;

private:
    // button indicator
    lv_style_t mButtonIndicatorStyle{};
    lv_obj_t* mButtonUpIndicator;
    lv_obj_t* mButtonDownIndicator;
};
