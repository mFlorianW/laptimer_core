#ifndef __POSITIONS__H__
#define __POSITIONS__H__

#include "PositionData.hpp"

namespace LaptimerCore::Test::Dummy
{

class Positions
{
public:
    static Common::PositionData getOscherslebenPositionCamp();

    const static Common::PositionData OscherslebenPositionCamp;
    const static Common::PositionData OscherslebenPositionStartFinishLine;
    const static Common::PositionData OscherslebenPositionSector1Line;
    const static Common::PositionData OscherslebenPositionSector2Line;

    const static Common::PositionData OscherslebenStartFinishLine1;
    const static Common::PositionData OscherslebenStartFinishLine2;
    const static Common::PositionData OscherslebenStartFinishLine3;
    const static Common::PositionData OscherslebenStartFinishLine4;

    const static Common::PositionData OscherslebenSector1Point1;
    const static Common::PositionData OscherslebenSector1Point2;
    const static Common::PositionData OscherslebenSector1Point3;
    const static Common::PositionData OscherslebenSector1Point4;

    const static Common::PositionData OscherslebenSector2Point1;
    const static Common::PositionData OscherslebenSector2Point2;
    const static Common::PositionData OscherslebenSector2Point3;
    const static Common::PositionData OscherslebenSector2Point4;
};

} // namespace LaptimerCore::Test::Dummy

#endif //!__POSITIONS__H__
