// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

class ICommand
{
public:
    virtual ~ICommand() = default;

    ICommand(ICommand const&) = default;

    ICommand& operator=(ICommand const&) = default;

    ICommand(ICommand&&) = default;

    ICommand& operator=(ICommand&&) = default;

    /**
     * Execute the commands.
     */
    virtual void execute() = 0;

protected:
    ICommand() = default;
};
