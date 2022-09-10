#include "Tracks.hpp"
#include "PositionData.hpp"
#include "Positions.hpp"

using namespace LaptimerCore::Common;

namespace LaptimerCore::Test::Dummy
{
TrackData Tracks::TrackWithoutSector{};
TrackData Tracks::OscherslebenTrack{};

void Tracks::init()
{
    TrackWithoutSector.setTrackName("TrackWithoutSector");
    TrackWithoutSector.setStartline(Positions::OscherslebenPositionCamp);
    TrackWithoutSector.setFinishline(Positions::OscherslebenPositionCamp);

    OscherslebenTrack.setTrackName("Oschersleben");
    OscherslebenTrack.setStartline(Positions::OscherslebenPositionCamp);
    OscherslebenTrack.setFinishline(Positions::OscherslebenPositionCamp);
    OscherslebenTrack.setSections({Positions::OscherslebenPositionCamp, Positions::OscherslebenPositionCamp});
}

} // namespace LaptimerCore::Test::Dummy
