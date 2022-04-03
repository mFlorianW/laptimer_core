#ifndef DATE_HPP
#define DATE_HPP

#include "SharedDataPointer.hpp"
#include <string>

namespace LaptimerCore::Common
{

class SharedDateData;
class Date
{
public:
    /**
     * Creates an instance of Date.
     */
    Date();

    /**
     * Default destructor
     */
    ~Date();

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

private:
    SharedDataPointer<SharedDateData> mData;
};

} // namespace LaptimerCore::Common

#endif // DATE_HPP
