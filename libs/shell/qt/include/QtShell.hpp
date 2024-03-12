// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef QTSHELL_HPP
#define QTSHELL_HPP

#include <QtGlobal>
#include <memory>

namespace LaptimerCore::QtShell
{
struct QtShellPrivate;
class QtShell final
{
    Q_DISABLE_COPY_MOVE(QtShell)
public:
    QtShell();

    ~QtShell();

    void show();

private:
    std::unique_ptr<QtShellPrivate> d;
};

} // namespace LaptimerCore::QtShell

#endif // QTSHELL_HPP
