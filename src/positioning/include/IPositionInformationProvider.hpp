#ifndef __IPOSITIONINFORMATIONPROVIDER__H__
#define __IPOSITIONINFORMATIONPROVIDER__H__

#include "PositionData.hpp"
#include <kdbindings/signal.h>
#include <vector>

namespace LaptimerCore::Positioning
{
/**
 * Interface for providing position information like the latitude, longitude, speed, height and time
 * information of GNSS module.
 */
class IPositionInformationProvider
{
public:
    /**
     * Default desctructor
     */
    virtual ~IPositionInformationProvider() = default;

    /**
     * Gives the last received position.
     * @return The last received position
     */
    virtual PositionData getPositionData() const = 0;

    /**
     * This signal is emitted when new position information are available.
     * @return Signal<> The signal object to get notified when new position informations are available.
     */
    KDBindings::Signal<> positionInformationReceived();

protected:
    /**
     * Default protected constructor
     */
    IPositionInformationProvider() = default;
};
} // namespace LaptimerCore::Positioning

#endif //!__IPOSITIONINFORMATIONPROVIDER__H__