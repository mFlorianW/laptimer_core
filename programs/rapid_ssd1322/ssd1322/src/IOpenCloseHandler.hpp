// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

class IOpenCloseHandler
{
public:
    virtual void open() = 0;

    virtual void close() = 0;
};
