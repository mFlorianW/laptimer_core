#include "MenuScreen.hpp"

MenuScreen::MenuScreen()
    : Screen()
{
    // init button indicator
    lv_style_init(&mButtonIndicatorStyle);
    lv_style_set_text_font(&mButtonIndicatorStyle, LV_STATE_DEFAULT, &lv_font_montserrat_28);

    mButtonUpIndicator = lv_label_create(m_screen, nullptr);
    lv_obj_add_style(mButtonUpIndicator, LV_LABEL_PART_MAIN, &mButtonIndicatorStyle);
    lv_label_set_text(mButtonUpIndicator, LV_SYMBOL_UP);
    lv_obj_align(mButtonUpIndicator, m_screen, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

    mButtonDownIndicator = lv_label_create(m_screen, nullptr);
    lv_obj_add_style(mButtonDownIndicator, LV_LABEL_PART_MAIN, &mButtonIndicatorStyle);
    lv_label_set_text(mButtonDownIndicator, LV_SYMBOL_DOWN);
    lv_obj_align(mButtonDownIndicator, m_screen, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 7);
}

MenuScreen::~MenuScreen()
{
    lv_obj_del(mButtonDownIndicator);
    lv_obj_del(mButtonUpIndicator);
}
