// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "NavigateDownCommand.hpp"
#include "../../include/ScreenModel.hpp"

NavigateDownCommand::NavigateDownCommand(INavigationHandler& handler)
    : mHandler(handler)
{
}

void NavigateDownCommand::execute()
{
    mHandler.navigateDown();
}