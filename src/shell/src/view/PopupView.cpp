#include "PopupView.hpp"
#include <cstdio>

PopupView::PopupView()
    : View()
{
    // A PopupView shall use the whole screen
    lv_obj_set_size(mScreenContent, 256, 64);
    lv_obj_set_pos(mScreenContent, 0, 0);

    // Setup the label style
    lv_style_init(&mLabelStyle);
    lv_style_set_text_font(&mLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    // Setup the cancel button
    mCancelLabel = lv_label_create(mScreenContent, nullptr);
    lv_obj_add_style(mCancelLabel, LV_LABEL_PART_MAIN, &mLabelStyle);
    lv_label_set_text(mCancelLabel, LV_SYMBOL_CLOSE);
    lv_obj_align(mCancelLabel, mScreenContent, LV_ALIGN_IN_TOP_LEFT, 3, -2);

    // Setup the confirmation button
    mConfirmLabel = lv_label_create(mScreenContent, nullptr);
    lv_label_set_text(mConfirmLabel, LV_SYMBOL_OK);
    lv_obj_add_style(mConfirmLabel, LV_LABEL_PART_MAIN, &mLabelStyle);
    lv_obj_align(mConfirmLabel, mScreenContent, LV_ALIGN_IN_BOTTOM_LEFT, 0, 5);

    // setup main text
    mMainText = lv_label_create(mScreenContent, nullptr);

    // setup main text
    mSecondaryText = lv_label_create(mScreenContent, nullptr);
}

PopupView::~PopupView()
{
    lv_obj_del(mConfirmLabel);
    lv_obj_del(mCancelLabel);
    lv_obj_del(mMainText);
    lv_obj_del(mSecondaryText);
}

void PopupView::setCloseCommand(ICommand *command)
{
    mCloseCommand = command;
}

bool PopupView::handleEnter()
{
    return handleEscape();
}

bool PopupView::handleEscape()
{
    if (mCloseCommand == nullptr)
    {
        return false;
    }

    mCloseCommand->execute();
    return true;
}

void PopupView::setMainText(const std::string &mainText)
{
    // TODO:
    // This is maybe a problem when the popup is reused with different text.
    // The positioning behaves sometimes very very weird.
    lv_label_set_text(mMainText, mainText.c_str());
    lv_label_set_align(mMainText, LV_LABEL_ALIGN_CENTER);
    lv_label_set_long_mode(mMainText, LV_LABEL_LONG_EXPAND);
    lv_obj_add_style(mMainText, LV_LABEL_PART_MAIN, &mLabelStyle);
    lv_obj_align(mMainText, nullptr, LV_ALIGN_IN_TOP_MID, lv_obj_get_width(mCancelLabel), 5);
}

void PopupView::setSecondaryText(const std::string &secondaryText)
{
    // TODO:
    // This is maybe a problem when the popup is reused with different text.
    // The positioning behaves sometimes very very weird.
    lv_label_set_text_fmt(mSecondaryText, "%s", secondaryText.c_str());
    lv_label_set_align(mSecondaryText, LV_LABEL_ALIGN_CENTER);
    lv_label_set_long_mode(mSecondaryText, LV_LABEL_LONG_EXPAND);
    lv_obj_add_style(mSecondaryText, LV_LABEL_PART_MAIN, &mLabelStyle);
    lv_obj_align(mSecondaryText, nullptr, LV_ALIGN_IN_TOP_MID, lv_obj_get_width(mCancelLabel), 29);
}

void PopupView::setType(Type type)
{
    mType = type;
    bool hide = false;
    if (mType == Type::NoConfirmation)
    {
        hide = true;
    }

    lv_obj_set_hidden(mConfirmLabel, hide);
    lv_obj_set_hidden(mCancelLabel, hide);
}