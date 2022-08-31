#include "MenuEntryView.hpp"
#include <lvgl.h>

MenuEntryView::MenuEntryView()
{
    // Setup View Container
    lv_obj_set_size(mScreenContent, 228, 64);
    lv_obj_set_pos(mScreenContent, 0, 0);

    // Setup entry label
    lv_style_init(&mEntryLabelStyle);
    lv_style_set_text_font(&mEntryLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    mEntryLabel = lv_label_create(mScreenContent, nullptr);
    lv_obj_add_style(mEntryLabel, LV_LABEL_PART_MAIN, &mEntryLabelStyle);
    lv_obj_set_size(mEntryLabel, lv_obj_get_width(mScreenContent), 24);
    lv_obj_set_x(mEntryLabel, 15);
    lv_obj_set_y(mEntryLabel, 10);

    // Setup secondary label
    lv_style_init(&mSecondaryEntryLabelStyle);
    lv_style_set_text_font(&mSecondaryEntryLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_16);

    mSecondaryEnrtyLabel = lv_label_create(mScreenContent, nullptr);
    lv_obj_add_style(mSecondaryEnrtyLabel, LV_LABEL_PART_MAIN, &mSecondaryEntryLabelStyle);
    lv_obj_set_size(mSecondaryEnrtyLabel, lv_obj_get_width(mScreenContent), 16);
    lv_obj_set_x(mSecondaryEnrtyLabel, 15);
    lv_obj_set_y(mSecondaryEnrtyLabel, 34);
}

void MenuEntryView::setEntryLabel(const std::string &entryLabel)
{
    mEntryLabelText = entryLabel;
    lv_label_set_text(mEntryLabel, mEntryLabelText.c_str());
}

void MenuEntryView::setSecondaryLabel(const std::string &secondaryLabel)
{
    mSecondaryEntryLabelText = secondaryLabel;
    lv_label_set_text(mSecondaryEnrtyLabel, mSecondaryEntryLabelText.c_str());
}

MenuEntryView::~MenuEntryView()
{
    lv_obj_del(mEntryLabel);
    lv_obj_del(mSecondaryEnrtyLabel);
}

bool MenuEntryView::handleEscape()
{
    printf("EntryView: Close called!\n");
    if (mCloseCommand == nullptr)
    {
        return false;
    }

    mCloseCommand->execute();
    return true;
}

bool MenuEntryView::handleButtonUp()
{
    if (mNavigateUpCommand == nullptr)
    {
        return false;
    }

    mNavigateUpCommand->execute();
    return true;
}

bool MenuEntryView::handleButtonDown()
{
    if (mNavigateDownCommand == nullptr)
    {
        return false;
    }

    mNavigateDownCommand->execute();
    return true;
}

bool MenuEntryView::handleEnter()
{
    printf("EntryView: Open called!\n");
    if (mOpenCommand == nullptr)
    {
        return false;
    }

    mOpenCommand->execute();
    return true;
}

void MenuEntryView::setNavigateUpCommand(ICommand *command)
{
    mNavigateUpCommand = command;
}

void MenuEntryView::setNavigateDownCommand(ICommand *command)
{
    mNavigateDownCommand = command;
}

void MenuEntryView::setOpenCommand(ICommand *command)
{
    mOpenCommand = command;
}

void MenuEntryView::setCloseCommand(ICommand *command)
{
    mCloseCommand = command;
}