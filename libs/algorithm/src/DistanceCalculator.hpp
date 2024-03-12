// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __DISTANCECALCULATOR__H__
#define __DISTANCECALCULATOR__H__

#include <PositionData.hpp>

namespace LaptimerCore::Algorithm::DistanceCalculator
{
/**
 * Calculates the between tow positions. The position is only accurate
 * when the expected distance is in the range of 1-2km.
 * @param pos1 The first position.
 * @param pos2 The second position.
 * @return float  The distance between the to points.
 */
float calculateDistance(Common::PositionData const& pos1, Common::PositionData const& pos2);
}; // namespace LaptimerCore::Algorithm::DistanceCalculator

#endif //!__DISTANCECALCULATOR__H__