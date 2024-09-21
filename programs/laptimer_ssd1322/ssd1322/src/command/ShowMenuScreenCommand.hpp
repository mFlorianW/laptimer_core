// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __SHOWMENUSCREENCOMMAND__H__
#define __SHOWMENUSCREENCOMMAND__H__

#include "ICommand.hpp"

class ScreenModel;
class ShowMenuScreenCommand : public ICommand
{
public:
    ShowMenuScreenCommand(ScreenModel& screenModel);
    ~ShowMenuScreenCommand() override = default;

    void execute() override;

private:
    ScreenModel& mScreenModel;
};

#endif //!__SHOWMENUSCREENCOMMAND__H__