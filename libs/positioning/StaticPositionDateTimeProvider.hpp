// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef STATICPOSITIONDATETIMEPROVIDER_HPP
#define STATICPOSITIONDATETIMEPROVIDER_HPP

#include "IPositionDateTimeProvider.hpp"
#include <Timestamp.hpp>

namespace Rapid::Positioning
{

class StaticPositionDateTimeProvider final : public IPositionDateTimeProvider
{
public:
    StaticPositionDateTimeProvider()
    {
        positionTimeData.set(
            Common::PositionDateTimeData{{52.0270889, 11.2803483}, Common::Timestamp{"15:05:10.234"}, {}});
    }

    /**
     * Default Destructor
     */
    ~StaticPositionDateTimeProvider() override = default;

    /**
     * Disabled copy operator
     */
    StaticPositionDateTimeProvider(StaticPositionDateTimeProvider const&) = delete;

    /**
     * Disabled copy operator
     */
    StaticPositionDateTimeProvider& operator=(StaticPositionDateTimeProvider const&) = delete;

    /**
     * Default move operator
     */
    StaticPositionDateTimeProvider(StaticPositionDateTimeProvider&&) noexcept = default;

    /**
     * Default move operator
     */
    StaticPositionDateTimeProvider& operator=(StaticPositionDateTimeProvider&&) noexcept = default;
};

} // namespace Rapid::Positioning

#endif // STATICPOSITIONDATETIMEPROVIDER_HPP
