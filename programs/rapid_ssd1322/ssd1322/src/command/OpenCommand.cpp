// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "OpenCommand.hpp"

OpenCommand::OpenCommand(IOpenCloseHandler& handler)
    : ICommand()
    , mHandler(handler)
{
}

void OpenCommand::execute()
{
    mHandler.open();
}