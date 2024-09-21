// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ICommand.hpp"
#include "IOpenCloseHandler.hpp"

class CloseCommand : public ICommand
{
public:
    CloseCommand(IOpenCloseHandler& handler);

    void execute() override;

private:
    IOpenCloseHandler& mHandler;
};
