#include "PositionInformationProvider.hpp"

namespace LaptimerCore::Test::Dummy
{

Common::PositionData PositionInformationProvider::getPositionData() const
{
    return positionData;
}

void PositionInformationProvider::setPositionData(Common::PositionData posData)
{
    positionData = posData;
    positionInformationReceived.emit();
}

} // namespace LaptimerCore::Test::Dummy