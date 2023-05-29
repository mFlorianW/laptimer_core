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
