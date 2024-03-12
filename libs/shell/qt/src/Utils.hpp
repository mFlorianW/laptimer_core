// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef UTILS_HPP
#define UTILS_HPP

#include <QString>
#include <Timestamp.hpp>

namespace LaptimerCore::QtShell
{

class Utils
{
public:
    static QString convertLaptimeToString(Common::Timestamp const& stamp);
};

} // namespace LaptimerCore::QtShell

#endif // UTILS_HPP
