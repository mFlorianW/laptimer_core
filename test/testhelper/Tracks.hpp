#ifndef __TRACKS__H__
#define __TRACKS__H__

#include "TrackData.hpp"

namespace LaptimerCore::TestHelper
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

} // namespace LaptimerCore::TestHelper

#endif //!__TRACKS__H__
