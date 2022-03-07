#include "Tracks.hpp"
#include "PositionData.hpp"

using namespace LaptimerCore::Common;

namespace LaptimerCore::Test::Dummy
{
TrackData Tracks::OscherslebenTrack{};

void Tracks::init()
{
    auto finishLine = PositionData{};
    finishLine.setLatitude(52.02718520);
    finishLine.setLongitude(11.27989104);
    OscherslebenTrack.setTrackName("Oschersleben");
    OscherslebenTrack.setFinishline(finishLine);
}

} // namespace LaptimerCore::Test::Dummy
