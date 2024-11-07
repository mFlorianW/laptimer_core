// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __ITRACKDETECTION__H__
#define __ITRACKDETECTION__H__

#include <PositionData.hpp>
#include <TrackData.hpp>

namespace Rapid::Algorithm
{

class ITrackDetection
{
public:
    virtual ~ITrackDetection() = default;

    /**
     * Checks if the given position is on the given track.
     * @param track The track to test if the position is on that track.
     * @param position The given position that shall be used for the check.
     * @return true The position is on the track.
     * @return false The position is not on the track.
     */
    virtual bool isOnTrack(Common::TrackData const& track, Common::PositionData const& position) const = 0;
};

} // namespace Rapid::Algorithm

#endif //!__ITRACKDETECTION__H__