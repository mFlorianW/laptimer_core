// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <IPositionDateTimeProvider.hpp>

namespace LaptimerCore::LappyHeadless
{

class LappyHeadless
{
public:
    LappyHeadless(LaptimerCore::Positioning::IPositionDateTimeProvider& posProvider);

private:
    LaptimerCore::Positioning::IPositionDateTimeProvider& mPositionProvider;
};

} // namespace LaptimerCore::LappyHeadless
