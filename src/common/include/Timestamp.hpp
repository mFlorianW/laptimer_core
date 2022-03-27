#ifndef __TIMESTAMP__H__
#define __TIMESTAMP__H__

#include "SharedDataPointer.hpp"
#include <cstdint>
#include <string>

namespace LaptimerCore::Common
{
class SharedTimestamp;
class Timestamp
{
public:
    /**
     * Creates an instance of Timestamp
     */
    Timestamp();

    /**
     * Default destructor
     */
    ~Timestamp();

    /**
     * Copy constructor for Timestamp.
     * @param other  The object to copy from.
     */
    Timestamp(const Timestamp &other);

    /**
     * The copy assignment operator for Timestamp.
     * @param other The object to copy from.
     * @return Timestamp& A reference to the copied Timestamp.
     */
    Timestamp &operator=(const Timestamp &other);

    /**
     * The move constructor for Timestamp.
     * @param other The object to move from.
     */
    Timestamp(Timestamp &&other);

    /**
     * The move assignment operator for timestamp.
     * @param other The object to move from.
     * @return Timestamp& A reference to the moved Timestamp.
     */
    Timestamp &operator=(Timestamp &&other);

    /**
     * Gives the hour.
     * @return std::uint8_t The hour of Timestamp.
     */
    std::uint8_t getHour() const;

    /**
     * Sets a new hour.
     * @param hour The new hour.
     */
    void setHour(std::uint8_t hour);

    /**
     * Gives the minute.
     * @return std::uint8_t The minute of Timestamp.
     */
    std::uint8_t getMinute() const;

    /**
     * Sets a new minute.
     * @param minute The new minute.
     */
    void setMinute(std::uint8_t minute);

    /**
     * Gives the second of the Timestamp.
     * @return std::uint8_t The second of Timestamp.
     */
    std::uint8_t getSecond() const;

    /**
     * Sets a new second.
     * @param second The new second.
     */
    void setSecond(std::uint8_t second);

    /**
     * Gives the fractional of a second.
     * @return std::uint16_t The fractional of a second.
     */
    std::uint16_t getFractionalOfSecond() const;

    /**
     * Sets a new fractional of second in Timestamp.
     * @param fractionalOfSecond The new fractional of second.
     */
    void setFractionalOfSecond(std::uint16_t fractionalOfSecond);

    /**
     * Converts the time compontes of the timestamp to a string.
     * The string will have the format of: 00:01:35.123
     * @return The time component to the timestamp as string.
     */
    std::string asString() const noexcept;

private:
    SharedDataPointer<SharedTimestamp> mData;
};

} // namespace LaptimerCore::Common

#endif //!__TIMESTAMP__H__
