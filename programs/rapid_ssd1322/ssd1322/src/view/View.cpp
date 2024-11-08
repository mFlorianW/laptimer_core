// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "View.hpp"

View::View()
    : mBackScreen(lv_obj_create(nullptr, nullptr))
    , mScreenContent(lv_cont_create(mBackScreen, nullptr))
{
    // configure content container
    lv_style_init(&mScreenContentStyle);
    lv_style_set_bg_color(&mScreenContentStyle, LV_CONT_PART_MAIN, LV_COLOR_BLACK);
    lv_style_set_border_width(&mScreenContentStyle, LV_CONT_PART_MAIN, 0);
    lv_obj_set_size(mScreenContent, 256, 48);
    lv_obj_set_pos(mScreenContent, 0, 16);
    lv_obj_add_style(mScreenContent, LV_CONT_PART_MAIN, &mScreenContentStyle);
}

View::~View()
{
    lv_obj_del(mScreenContent);
    lv_obj_del(mBackScreen);
}

lv_obj_t* View::get_screen_content() const
{
    return mScreenContent;
}

void View::handleButtonDown()
{
    if (mDownCommand) {
        mDownCommand->execute();
    }
}

void View::handleButtonUp()
{
    if (mUpCommand) {
        mUpCommand->execute();
    }
}

void View::handleEscape()
{
    if (mEscapeCommand) {
        mEscapeCommand->execute();
    }
}

void View::handleEnter()
{
    if (mEnterCommand) {
        mEnterCommand->execute();
    }
}

void View::setNavigateUpCommand(ICommand* command)
{
    mUpCommand = command;
}

void View::setNavigateDownCommand(ICommand* command)
{
    mDownCommand = command;
}

void View::setOpenCommand(ICommand* command)
{
    mEnterCommand = command;
}

void View::setCloseCommand(ICommand* command)
{
    mEscapeCommand = command;
}

bool View::isVisible() const
{
    return mVisible;
}

void View::setVisible(bool visible) noexcept
{
    mVisible = visible;
}
