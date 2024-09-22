// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <GlobalSettingsWriter.hpp>
#include <QQmlApplicationEngine>

namespace LaptimerCore::LappyShell
{

class LappyShell
{
public:
    LappyShell();

    void show() const noexcept;

private:
    void setupDatabase() noexcept;
    QQmlApplicationEngine mEngine{};
    Common::QSettingsBackend mSettingsBackend;
    GlobalSettingsWriter mSettings;
};

} // namespace LaptimerCore::LappyShell
