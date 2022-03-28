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
    Positions::init();

    TrackWithoutSector.setTrackName("TrackWithoutSector");
    TrackWithoutSector.setStartline(Positions::OscherslebenPosition);
    TrackWithoutSector.setFinishline(Positions::OscherslebenPosition);

    OscherslebenTrack.setTrackName("Oschersleben");
    OscherslebenTrack.setStartline(Positions::OscherslebenPosition);
    OscherslebenTrack.setFinishline(Positions::OscherslebenPosition);
    OscherslebenTrack.setSections({Positions::OscherslebenPosition, Positions::OscherslebenPosition});
}

} // namespace LaptimerCore::Test::Dummy
