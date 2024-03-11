#ifndef UTILS_HPP
#define UTILS_HPP

#include <QString>
#include <Timestamp.hpp>

namespace LaptimerCore::QtShell
{

class Utils
{
public:
    static QString convertLaptimeToString(Common::Timestamp const& stamp);
};

} // namespace LaptimerCore::QtShell

#endif // UTILS_HPP
