#ifndef POSITIONDATETIMEDATA_HPP
#define POSITIONDATETIMEDATA_HPP

#include "Date.hpp"
#include "PositionData.hpp"
#include "SharedDataPointer.hpp"
#include "Timestamp.hpp"

namespace LaptimerCore::Common
{

class SharedPositionDataTimeData;
class PositionDateTimeData final
{
public:
    /**
     * Creates an empty instance of PositionDateTimeDate
     */
    PositionDateTimeData();

    /**
     * Default destructor
     */
    ~PositionDateTimeData();

    /**
     * @return The current position
     */
    PositionData getPosition() const noexcept;

    /**
     * Sets a new position.
     * @param position The new position.
     */
    void setPosition(const PositionData &position);

    /**
     * @return The current time
     */
    Timestamp getTime() const noexcept;

    /**
     * Sets a new time.
     * @param time The new time.
     */
    void setTime(const Timestamp &time);

    /**
     * @return The current date.
     */
    Date getDate() const noexcept;

    /**
     * Sets a new date.
     * @param date The new date.
     */
    void setDate(const Date &date);

    /**
     * Equal operator
     * @return true The two objects are the same.
     * @return false The two objects are not the same.
     */
    friend bool operator==(const PositionDateTimeData &lhs, const PositionDateTimeData &rhs);

    /**
     * Not Equal operator
     * @return true The two objects are not the same.
     * @return false The two objects are the same.
     */
    friend bool operator!=(const PositionDateTimeData &lhs, const PositionDateTimeData &rhs);

private:
    SharedDataPointer<SharedPositionDataTimeData> mData;
};

} // namespace LaptimerCore::Common

#endif // POSITIONDATETIMEDATA_HPP
