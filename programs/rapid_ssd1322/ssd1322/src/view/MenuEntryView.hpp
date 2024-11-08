// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "View.hpp"
#include <string>

class MenuEntryView : public View
{
public:
    MenuEntryView();
    ~MenuEntryView() override;

    // Delete copy constructor
    MenuEntryView(MenuEntryView const&) = delete;

    // Delete copy assignment operator
    MenuEntryView& operator=(MenuEntryView const&) = delete;

    // Delete move constructor
    MenuEntryView(MenuEntryView&&) = delete;

    // Delete move assignment operator
    MenuEntryView& operator=(MenuEntryView&&) = delete;

    void setEntryLabel(std::string const& entryLabel);
    void setSecondaryLabel(std::string const& entryLabel);

private:
    lv_style_t mEntryLabelStyle{};
    lv_obj_t* mEntryLabel;
    lv_style_t mSecondaryEntryLabelStyle{};
    lv_obj_t* mSecondaryEnrtyLabel;

    std::string mEntryLabelText;
    std::string mSecondaryEntryLabelText;
};
