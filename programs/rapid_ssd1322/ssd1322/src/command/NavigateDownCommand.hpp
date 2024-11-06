// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "ICommand.hpp"
#include "INavigationHandler.hpp"

class NavigateDownCommand : public ICommand
{
public:
    NavigateDownCommand(INavigationHandler& handler);

    void execute() override;

private:
    INavigationHandler& mHandler;
};
