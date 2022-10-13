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

lv_obj_t *View::get_screen_content() const
{
    return mScreenContent;
}

bool View::handleButtonDown()
{
    return false;
}

bool View::handleButtonUp()
{
    return false;
}

bool View::handleEscape()
{
    return false;
}

bool View::handleEnter()
{
    return false;
}

void View::setCloseCommand(ICommand *command)
{
}
