#ifndef __TRACKS__H__
#define __TRACKS__H__

#include "TrackData.hpp"

namespace LaptimerCore::Test::Dummy
{

class Tracks
{
public:
    static void init();

    static Common::TrackData getOscherslebenTrack();

    const static Common::TrackData TrackWithoutSector;
    const static Common::TrackData OscherslebenTrack;
    const static Common::TrackData OscherslebenTrack2;
};

} // namespace LaptimerCore::Test::Dummy

#endif //!__TRACKS__H__
