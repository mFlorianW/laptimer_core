// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <IGPSInformationProvider.hpp>
#include <kdbindings/signal.h>

class StatusBarModel
{
public:
    explicit StatusBarModel(LaptimerCore::Positioning::IGpsInformationProvider& gpsInfoProvider);

    std::uint8_t getNumberOfStatellites() const;

    KDBindings::Signal<> numberOfSatellitesChanged;

private:
    LaptimerCore::Positioning::IGpsInformationProvider& mGpsInfoProvider;
};