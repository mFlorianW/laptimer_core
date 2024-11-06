// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ICommand.hpp"

class ScreenModel;
class ShowMainScreenCommand : public ICommand
{
public:
    ShowMainScreenCommand(ScreenModel& screenModel);

    void execute() override;

private:
    ScreenModel& mScreenModel;
};
