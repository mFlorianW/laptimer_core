// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef IPOSITIONDATETIMEPROVIDER_HPP
#define IPOSITIONDATETIMEPROVIDER_HPP

#include "PositionDateTimeData.hpp"
#include <kdbindings/property.h>

namespace Rapid::Positioning
{

class IPositionDateTimeProvider
{
public:
    /**
     *  Virtual default destructor.
     */
    virtual ~IPositionDateTimeProvider() = default;

    /**
     * This property holds current PostionDateTimeData
     */
    KDBindings::Property<Common::PositionDateTimeData> positionTimeData;

protected:
    /**
     * Default protected constructor.
     */
    IPositionDateTimeProvider() = default;
};

} // namespace Rapid::Positioning

#endif // IPOSITIONDATETIMEPROVIDER_HPP
