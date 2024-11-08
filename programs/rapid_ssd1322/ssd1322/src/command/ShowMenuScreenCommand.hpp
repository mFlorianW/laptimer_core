// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ICommand.hpp"

class ScreenModel;
class ShowMenuScreenCommand : public ICommand
{
public:
    ShowMenuScreenCommand(ScreenModel& screenModel);

    void execute() override;

private:
    ScreenModel& mScreenModel;
};
