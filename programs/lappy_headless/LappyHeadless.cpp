// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "LappyHeadless.hpp"

namespace LaptimerCore::LappyHeadless
{

LappyHeadless::LappyHeadless(LaptimerCore::Positioning::IPositionDateTimeProvider& posProvider,
                             LaptimerCore::Storage::ISessionDatabase& sessionDatabase,
                             LaptimerCore::Storage::ITrackDatabase& trackDatabase)
    : mPositionProvider{posProvider}
    , mSessionDatabase{sessionDatabase}
    , mTrackDatabase{trackDatabase}
{
}

} // namespace LaptimerCore::LappyHeadless
