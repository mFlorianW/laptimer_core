// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "NavigateUpCommand.hpp"
#include "../../include/ScreenModel.hpp"

NavigateUpCommand::NavigateUpCommand(INavigationHandler& handler)
    : mHandler(handler)
{
}

void NavigateUpCommand::execute()
{
    mHandler.navigateUp();
}