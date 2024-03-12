// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ShowMainScreenCommand.hpp"
#include "../../include/ScreenModel.hpp"

ShowMainScreenCommand::ShowMainScreenCommand(ScreenModel& screenModel)
    : mScreenModel(screenModel)
{
}

void ShowMainScreenCommand::execute()
{
    mScreenModel.activateMainScreen();
}