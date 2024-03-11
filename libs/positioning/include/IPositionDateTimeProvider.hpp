#ifndef IPOSITIONDATETIMEPROVIDER_HPP
#define IPOSITIONDATETIMEPROVIDER_HPP

#include "PositionDateTimeData.hpp"
#include <kdbindings/property.h>

namespace LaptimerCore::Positioning
{

class IPositionDateTimeProvider
{
public:
    /**
     *  Virtual default destructor.
     */
    virtual ~IPositionDateTimeProvider() = default;

    /**
     * This property holds current PostionDateTimeData
     */
    KDBindings::Property<Common::PositionDateTimeData> positionTimeData;

protected:
    /**
     * Default protected constructor.
     */
    IPositionDateTimeProvider() = default;
};

} // namespace LaptimerCore::Positioning

#endif // IPOSITIONDATETIMEPROVIDER_HPP
