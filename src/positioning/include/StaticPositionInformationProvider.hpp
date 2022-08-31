#ifndef LAPTIMERCORE_STATICPOSITIONINFORMATIONPROVIDER_HPP
#define LAPTIMERCORE_STATICPOSITIONINFORMATIONPROVIDER_HPP

#include "IPositionInformationProvider.hpp"

namespace LaptimerCore::Positioning
{

class StaticPositionInformationProvider : public IPositionInformationProvider
{
public:
    Common::PositionData getPositionData() const override
    {
        return Common::PositionData{};
    }
};

} // namespace LaptimerCore::Positioning
#endif // LAPTIMERCORE_STATICPOSITIONINFORMATIONPROVIDER_HPP
