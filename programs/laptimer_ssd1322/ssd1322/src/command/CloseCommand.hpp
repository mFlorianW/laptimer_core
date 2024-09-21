// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __CLOSECOMMAND__H__
#define __CLOSECOMMAND__H__

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

#endif //!__CLOSECOMMAND__H__