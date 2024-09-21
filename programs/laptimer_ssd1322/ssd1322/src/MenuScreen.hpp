// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __MENUSCREEN__H__
#define __MENUSCREEN__H__

#include "Screen.hpp"
#include <lvgl.h>

class MenuScreen : public Screen
{
public:
    MenuScreen();
    ~MenuScreen();

private:
    // button indicator
    lv_style_t mButtonIndicatorStyle;
    lv_obj_t* mButtonUpIndicator;
    lv_obj_t* mButtonDownIndicator;
};

#endif //!__MENUSCREEN__H__