#ifndef STATICPOSITIONDATETIMEPROVIDER_HPP
#define STATICPOSITIONDATETIMEPROVIDER_HPP

#include "IPositionDateTimeProvider.hpp"
#include <Timestamp.hpp>

namespace LaptimerCore::Positioning
{

class StaticPositionDateTimeProvider final : public IPositionDateTimeProvider
{
public:
    StaticPositionDateTimeProvider()
    {
        positionTimeData.set(
            Common::PositionDateTimeData{{52.0270889, 11.2803483}, Common::Timestamp{"15:05:10.234"}, {}});
    }

    ~StaticPositionDateTimeProvider()
    {
    }
};

} // namespace LaptimerCore::Positioning

#endif // STATICPOSITIONDATETIMEPROVIDER_HPP
