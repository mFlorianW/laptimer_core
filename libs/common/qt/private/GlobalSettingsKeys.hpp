// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QString>

/**
 * @file
 * This file contains the keys for the global settings
 */

namespace LaptimerCore::Common::Private
{

/**
 * Settings key for the database file path
 * The file path is used by the application to know which database file shall be loaded.
 */
constexpr auto DbFilePathKey = QStringView(u"dbFilePath");

} // namespace LaptimerCore::Common::Private
