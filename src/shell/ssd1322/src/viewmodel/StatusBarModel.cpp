#include "StatusBarModel.hpp"

StatusBarModel::StatusBarModel(LaptimerCore::Positioning::IGpsInformationProvider &gpsInfoProvider)
    : mGpsInfoProvider{gpsInfoProvider}

{
    mGpsInfoProvider.numberOfSatellitesChanged.connect([=] { numberOfSatellitesChanged.emit(); });
}

std::uint8_t StatusBarModel::getNumberOfStatellites() const
{
    return mGpsInfoProvider.getNumbersOfStatelite();
}