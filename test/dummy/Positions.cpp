#include "Positions.hpp"

using namespace LaptimerCore::Common;

namespace LaptimerCore::Test::Dummy
{
PositionData Positions::OscherslebenPosition{};

void Positions::init()
{
    OscherslebenPosition.setLatitude(52.0258333);
    OscherslebenPosition.setLongitude(11.279166666);
}

} // namespace LaptimerCore::Test::Dummy
