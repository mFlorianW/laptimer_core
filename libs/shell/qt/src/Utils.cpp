#include <Utils.hpp>

namespace LaptimerCore::QtShell
{

QString Utils::convertLaptimeToString(Common::Timestamp const& stamp)
{
    auto convertedLaptime = QString{"%1:%2:%3.%4"}
                                .arg(stamp.getHour(), 2, 10, QChar{'0'})
                                .arg(stamp.getMinute(), 2, 10, QChar{'0'})
                                .arg(stamp.getSecond(), 2, 10, QChar{'0'})
                                .arg(stamp.getFractionalOfSecond(), 3, 10, QChar{'0'});
    return convertedLaptime;
}

} // namespace LaptimerCore::QtShell
