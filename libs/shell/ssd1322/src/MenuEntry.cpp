// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "MenuEntry.hpp"
#include "View.hpp"
#include <iostream>

MenuEntry::MenuEntry()
    : IOpenCloseHandler()
    , mEnterCommand{*this}
    , mEscapeCommand{*this}
{
}

View* MenuEntry::getMenuEntryView() const noexcept
{
    return mActiveView;
}

void MenuEntry::setMenuEntryView(View* view) noexcept
{
    if (view == nullptr) {
        return;
    }

    mEntryView = view;
    mEntryView->setOpenCommand(&mEnterCommand);
    mEntryView->setCloseCommand(&mEscapeCommand);
    mActiveView = view;
}

void MenuEntry::addMenuEntry(IMenuEntry* entry) noexcept
{
    if (entry == nullptr) {
        return;
    }

    mMenuEntry = entry;
    mMenuEntry->viewChanged.connect([=]() {
        mActiveView = mMenuEntry->getMenuEntryView();
        viewChanged.emit();
    });
}

void MenuEntry::open()
{
    if (mMenuEntry == nullptr) {
        return;
    }

    mActiveView = mMenuEntry->getMenuEntryView();
    mActiveView->setCloseCommand(&mEscapeCommand);
    viewChanged.emit();
}

void MenuEntry::close()
{
    mActiveView = mEntryView;
    closeEntry.emit();
}
