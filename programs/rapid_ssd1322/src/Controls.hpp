// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <lv_obj.h>

class Controls final
{
public:
    Controls();
    ~Controls();
    Controls& operator=(Controls const&) = delete;
    Controls(Controls const&) = delete;
    Controls& operator=(Controls&&) noexcept = delete;
    Controls(Controls const&&) noexcept = delete;

private:
    static void xButtonPressed(lv_obj_t* obj, lv_event_t event);
    static void oButtonPressed(lv_obj_t* obj, lv_event_t event);
    static void upButtonPressed(lv_obj_t* obj, lv_event_t event);
    static void downButtonPressed(lv_obj_t* obj, lv_event_t event);

private:
    lv_style_t mFontStyle{};

    lv_obj_t* mXButton;
    lv_obj_t* mXButtonLabel;
    lv_obj_t* mOButton;
    lv_obj_t* mOButtonLabel;
    lv_obj_t* mUpButton;
    lv_obj_t* mUpButtonLabel;
    lv_obj_t* mDownButton;
    lv_obj_t* mDownButtonLabel;
};
