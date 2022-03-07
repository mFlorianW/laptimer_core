#ifndef __POSITIONINFORMATIONPROVIDER__H__
#define __POSITIONINFORMATIONPROVIDER__H__

#include "IPositionInformationProvider.hpp"
#include "PositionData.hpp"

namespace LaptimerCore::Test::Dummy
{

class PositionInformationProvider : public Positioning::IPositionInformationProvider
{
public:
    Common::PositionData getPositionData() const override;
    void setPositionData(Common::PositionData posData);

    Common::PositionData positionData;
};

} // namespace LaptimerCore::Test::Dummy

#endif //!__POSITIONINFORMATIONPROVIDER__H__