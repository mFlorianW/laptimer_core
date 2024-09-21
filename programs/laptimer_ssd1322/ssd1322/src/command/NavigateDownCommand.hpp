// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __NAVIGATEDOWNCOMMAND__H__
#define __NAVIGATEDOWNCOMMAND__H__

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

#endif //!__NAVIGATEDOWNCOMMAND__H__