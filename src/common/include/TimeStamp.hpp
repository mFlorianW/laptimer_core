#ifndef __TIMESTAMP__H__
#define __TIMESTAMP__H__

#include <cstdint>

namespace LaptimerCore::Common
{
struct Timestamp
{
    std::uint8_t hour;
    std::uint8_t minute;
    std::uint8_t seconds;
    std::uint16_t fractionalOfSecond;
};

} // namespace LaptimerCore::Common

#endif //!__TIMESTAMP__H__