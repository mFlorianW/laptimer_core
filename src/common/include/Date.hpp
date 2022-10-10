#ifndef DATE_HPP
#define DATE_HPP

#include "SharedDataPointer.hpp"
#include <string>

namespace LaptimerCore::Common
{

class SharedDate;
class Date final
{
public:
    /**
     * Creates an instance of Date.
     */
    Date();

    /**
     * Creates a date by a string.
     * The string must have the format dd.MM.YYYY
     * @param dateString
     */
    Date(const std::string &dateString);

    /**
     * Default destructor
     */
    ~Date();

    /**
     * Copy constructor for Date
     * @param ohter The object to copy from.
     */
    Date(const Date &ohter);

    /**
     * The copy assignment operator for Date.
     * @param other The object to copy from.
     * @return TrackData& A reference to the copied track.
     */
    Date &operator=(const Date &other);

    /**
     * Move constructor for Date
     * @param other The object to move from.
     */
    Date(Date &&other);

    /**
     * The move assignment operator for the Date.
     * @param other The object to move from.
     * @return TrackData& A reference to the moved date.
     */
    Date &operator=(Date &&other);

    /**
     * Gives the year.
     * @return The year of the date.
     */
    std::uint16_t getYear() const noexcept;

    /**
     * Sets a new year.
     * @param year The new year.
     */
    void setYear(std::uint16_t year);

    /**
     * Gives the month.
     * @return The month of the date.
     */
    std::uint8_t getMonth() const noexcept;

    /**
     * Sets a new month.
     * @param month The new month.
     */
    void setMonth(std::uint8_t month);

    /**
     * Gives the the day.
     * @return The day of the date.
     */
    std::uint8_t getDay() const noexcept;

    /**
     * Sets a new day.
     * @param day The day of the date.
     */
    void setDay(std::uint8_t day);

    /**
     * Converts the date into string in the format of dd.MM.YYYY
     * @return The date as string.
     */
    std::string asString() const noexcept;

    /**
     * Equal operator
     * @return true The two objects are the same.
     * @return false The two objects are not the same.
     */
    friend bool operator==(const Date &lhs, const Date &rhs);

    /**
     * Not Equal operator
     * @return true The two objects are not the same.
     * @return false The two objects are the same.
     */
    friend bool operator!=(const Date &lhs, const Date &rhs);

    /**
     * Gives you the date of the system
     * @return Date object with the system date.
     */
    static Date getSystemDate() noexcept;

private:
    SharedDataPointer<SharedDate> mData;
};

} // namespace LaptimerCore::Common

#endif // DATE_HPP
