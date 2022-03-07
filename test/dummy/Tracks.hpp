#ifndef __TRACKS__H__
#define __TRACKS__H__

#include "PositionData.hpp"
#include "TrackData.hpp"

namespace LaptimerCore::Test::Dummy
{

class Tracks
{
public:
    static void init();

    static Common::TrackData OscherslebenTrack;
};

} // namespace LaptimerCore::Test::Dummy

#endif //!__TRACKS__H__