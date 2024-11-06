// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "MainScreenView.hpp"
#include <cstdio>

void MainScreenView::handleEnter()
{
    if (mNavigateMenuCommand == nullptr) {
        return;
    }

    mNavigateMenuCommand->execute();
}

void MainScreenView::setShowMenuScreenCommand(ICommand* command)
{
    mNavigateMenuCommand = command;
}
