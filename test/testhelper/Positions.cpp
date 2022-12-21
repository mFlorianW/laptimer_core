#include "Positions.hpp"

using namespace LaptimerCore::Common;

namespace LaptimerCore::TestHelper
{

const PositionData Positions::OscherslebenPositionCamp{52.0258333, 11.279166666};
const PositionData Positions::OscherslebenPositionStartFinishLine{52.0270889, 11.2803483};
const PositionData Positions::OscherslebenPositionSector1Line{52.0298205, 11.2741851};
const PositionData Positions::OscherslebenPositionSector2Line{52.0299681, 11.2772076};

const PositionData Positions::OscherslebenStartFinishLine1{52.0270444, 11.2805431};
const PositionData Positions::OscherslebenStartFinishLine2{52.0270730, 11.2804234};
const PositionData Positions::OscherslebenStartFinishLine3{52.0271084, 11.2802563};
const PositionData Positions::OscherslebenStartFinishLine4{52.0271438, 11.2800835};

const PositionData Positions::OscherslebenSector1Point1{52.029819, 11.274203};
const PositionData Positions::OscherslebenSector1Point2{52.029821, 11.274193};
const PositionData Positions::OscherslebenSector1Point3{52.029821, 11.274169};
const PositionData Positions::OscherslebenSector1Point4{52.029822, 11.274149};

const PositionData Positions::OscherslebenSector2Point1{52.029970, 11.277183};
const PositionData Positions::OscherslebenSector2Point2{52.029968, 11.277193};
const PositionData Positions::OscherslebenSector2Point3{52.029967, 11.277212};
const PositionData Positions::OscherslebenSector2Point4{52.029966, 11.277218};

PositionData Positions::getOscherslebenPositionCamp()
{
    return Common::PositionData{52.0258333, 11.279166666};
}

} // namespace LaptimerCore::TestHelper
