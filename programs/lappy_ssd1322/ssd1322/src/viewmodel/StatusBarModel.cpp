// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "StatusBarModel.hpp"

StatusBarModel::StatusBarModel(Rapid::Positioning::IGpsInformationProvider& gpsInfoProvider)
    : mGpsInfoProvider{gpsInfoProvider}

{
    mGpsInfoProvider.numberOfSatellitesChanged.connect([=] {
        numberOfSatellitesChanged.emit();
    });
}

std::uint8_t StatusBarModel::getNumberOfStatellites() const
{
    return mGpsInfoProvider.getNumbersOfStatelite();
}