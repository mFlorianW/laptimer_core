// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "LappyHeadless.hpp"

namespace LaptimerCore::LappyHeadless
{

LappyHeadless::LappyHeadless(LaptimerCore::Positioning::IPositionDateTimeProvider& posProvider,

                             LaptimerCore::Storage::ISessionDatabase& sessionDatabase)
    : mPositionProvider{posProvider}
    , mSessionDatabase{sessionDatabase}
{
}

} // namespace LaptimerCore::LappyHeadless
