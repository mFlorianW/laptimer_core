// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ShowMenuScreenCommand.hpp"
#include "../../include/ScreenModel.hpp"

ShowMenuScreenCommand::ShowMenuScreenCommand(ScreenModel& screenModel)
    : mScreenModel(screenModel)
{
}

void ShowMenuScreenCommand::execute()
{
    mScreenModel.activateMenuScreen();
}