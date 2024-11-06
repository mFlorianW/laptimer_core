// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef POSITIONDATETIMEDATA_HPP
#define POSITIONDATETIMEDATA_HPP

#include "Date.hpp"
#include "PositionData.hpp"
#include "SharedDataPointer.hpp"
#include "Timestamp.hpp"

namespace Rapid::Common
{

class SharedPositionTimeData;
class PositionDateTimeData final
{
public:
    /**
     * Creates an empty instance of PositionDateTimeDate
     */
    PositionDateTimeData();

    /**
     * Creates an instance of the PositionDateTimeData.
     * @param posData The position data for the instance.
     * @param time The time data for the instance.
     * @param date The date data for the instance.
     */
    PositionDateTimeData(PositionData const& posData, Timestamp const& time, Date const& date);

    /**
     * Default destructor
     */
    ~PositionDateTimeData();

    /**
     * Copy constructor for PositionDateTimeData.
     * @param other The object to copy from.
     */
    PositionDateTimeData(PositionDateTimeData const& other);

    /**
     * Copy assignment operator for PositionDateTimeData.
     * @param other The object to copy from.
     * @return PositionData& A reference to the copied instance.
     */
    PositionDateTimeData& operator=(PositionDateTimeData const& other);

    /**
     * The move constructor for PositionDateTimeData.
     * @param other The object to move from.
     */
    PositionDateTimeData(PositionDateTimeData&& other);

    /**
     * The move assignment operator for PositionDateTimeData.
     * @param other The object to move from.
     * @return PositionData& A reference of the moved instance.
     */
    PositionDateTimeData& operator=(PositionDateTimeData&& other);

    /**
     * @return The current position
     */
    PositionData getPosition() const noexcept;

    /**
     * Sets a new position.
     * @param position The new position.
     */
    void setPosition(PositionData const& position);

    /**
     * @return The current time
     */
    Timestamp getTime() const noexcept;

    /**
     * Sets a new time.
     * @param time The new time.
     */
    void setTime(Timestamp const& time);

    /**
     * @return The current date.
     */
    Date getDate() const noexcept;

    /**
     * Sets a new date.
     * @param date The new date.
     */
    void setDate(Date const& date);

    /**
     * Equal operator
     * @return true The two objects are the same.
     * @return false The two objects are not the same.
     */
    friend bool operator==(PositionDateTimeData const& lhs, PositionDateTimeData const& rhs);

    /**
     * Not Equal operator
     * @return true The two objects are not the same.
     * @return false The two objects are the same.
     */
    friend bool operator!=(PositionDateTimeData const& lhs, PositionDateTimeData const& rhs);

private:
    SharedDataPointer<SharedPositionTimeData> mData;
};

} // namespace Rapid::Common

#endif // POSITIONDATETIMEDATA_HPP
