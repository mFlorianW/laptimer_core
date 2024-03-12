// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __ICOMMAND__H__
#define __ICOMMAND__H__

class ICommand
{
public:
    virtual ~ICommand() = default;

    /**
     * Execute the commands.
     */
    virtual void execute() = 0;
};

#endif //!__ICOMMAND__H__