// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ICommand.hpp"
#include "INavigationHandler.hpp"

class NavigateUpCommand : public ICommand
{
public:
    NavigateUpCommand(INavigationHandler& screenModel);

    void execute() override;

private:
    INavigationHandler& mHandler;
};
