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
     * Gives a reference list to the latest received positions informations.
     * @return const vector<PositionData>&
     */
    virtual const vector<PositionData> &getPositionData() const = 0;

    /**
     * This signal is emitted when new position information are available.
     * @return Signal<> The signal object to get notified when new position informations are available.
     */
    Signal<> positionInformationReceived();

protected:
    /**
     * Default protected constructor
     */
    IPositionInformationProvider() = default;
};
} // namespace LaptimerCore::Positioning

#endif //!__IPOSITIONINFORMATIONPROVIDER__H__