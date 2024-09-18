// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QQmlApplicationEngine>

namespace LaptimerCore::LappyShell
{

class LappyShell
{
public:
    LappyShell();

    void show() const noexcept;

private:
    QQmlApplicationEngine mEngine{};
};

} // namespace LaptimerCore::LappyShell
