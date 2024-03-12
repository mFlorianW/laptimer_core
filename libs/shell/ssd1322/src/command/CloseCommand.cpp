// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "CloseCommand.hpp"

CloseCommand::CloseCommand(IOpenCloseHandler& handler)
    : ICommand()
    , mHandler(handler)
{
}

void CloseCommand::execute()
{
    mHandler.close();
}