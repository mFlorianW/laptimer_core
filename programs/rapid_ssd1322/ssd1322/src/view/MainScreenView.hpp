// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ICommand.hpp"
#include "View.hpp"

class MainScreenView : public View
{
public:
    void handleEnter() final;

    void setShowMenuScreenCommand(ICommand* command);

protected:
    ICommand* mNavigateMenuCommand;
};
