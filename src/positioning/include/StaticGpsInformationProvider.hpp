#ifndef LAPTIMERCORE_STATICGPSINFORMATIONPROVIDER_HPP
#define LAPTIMERCORE_STATICGPSINFORMATIONPROVIDER_HPP

#include "IGPSInformationProvider.hpp"
namespace LaptimerCore::Positioning
{

class StaticGpsInformationProvider : public IGpsInformationProvider
{
public:
    uint8_t getNumbersOfStatelite() const override
    {
        return 0;
    }
};

} // namespace LaptimerCore::Positioning
#endif // LAPTIMERCORE_STATICGPSINFORMATIONPROVIDER_HPP
