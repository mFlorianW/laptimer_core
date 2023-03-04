#pragma once

#include "MainWindowModel.hpp"
#include <QHostAddress>
#include <QQmlApplicationEngine>

namespace LaptimerCore::SessionDl
{

class SessionDl final
{
public:
    SessionDl(QHostAddress const &dlAddress, quint16 port) noexcept;

    void show() const noexcept;

private:
    QQmlApplicationEngine mEngine;
    MainWindowModel mMainWindowModel;
};

} // namespace LaptimerCore::SessionDl
