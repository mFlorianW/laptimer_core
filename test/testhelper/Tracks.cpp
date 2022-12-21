#include "Tracks.hpp"
#include "PositionData.hpp"
#include "Positions.hpp"

using namespace LaptimerCore::Common;

namespace LaptimerCore::TestHelper
{
namespace
{
Common::TrackData createTrackWithoutSector()
{
    auto trackWithoutSector = TrackData{};
    trackWithoutSector.setTrackName("TrackWithoutSector");
    trackWithoutSector.setStartline(Positions::getOscherslebenPositionCamp());
    trackWithoutSector.setFinishline(Positions::getOscherslebenPositionCamp());

    return trackWithoutSector;
}

Common::TrackData createOscherslebenTrack()
{
    auto oschersleben = TrackData{};
    oschersleben.setTrackName("Oschersleben");
    oschersleben.setStartline(Positions::getOscherslebenPositionCamp());
    oschersleben.setFinishline(Positions::getOscherslebenPositionCamp());
    oschersleben.setSections({Positions::getOscherslebenPositionCamp(), Positions::getOscherslebenPositionCamp()});

    return oschersleben;
}

Common::TrackData createOscherslebenTrack2()
{
    auto oschersleben = TrackData{};
    oschersleben.setTrackName("Oschersleben");
    oschersleben.setStartline(Positions::getOscherslebenPositionCamp());
    oschersleben.setFinishline(Positions::getOscherslebenPositionCamp());
    oschersleben.setSections({Positions::getOscherslebenPositionCamp(), Common::PositionData{52.258335, 11.279166666}});

    return oschersleben;
}
} // namespace
const TrackData Tracks::TrackWithoutSector{createTrackWithoutSector()};
const TrackData Tracks::OscherslebenTrack{createOscherslebenTrack()};
const TrackData Tracks::OscherslebenTrack2{createOscherslebenTrack2()};

void Tracks::init()
{
}

TrackData Tracks::getOscherslebenTrack()
{
    return createOscherslebenTrack();
}

} // namespace LaptimerCore::TestHelper
