#ifndef __IGPSINFORMATIONPROVIDER__H__
#define __IGPSINFORMATIONPROVIDER__H__

#include <kdbindings/signal.h>

namespace LaptimerCore::Positioning
{

/**
 * Interface for providing GPS information
 */
class IGpsInformationProvider
{
public:
    virtual ~IGpsInformationProvider() = default;

    /**
     * Gives the number of the connted satellites.
     * @return std::uint8_t
     */
    virtual std::uint8_t getNumbersOfStatelite() const = 0;

    /**
     * This signal is emitted when the number of statellites changes.
     * @return Signal<> The signal object to get notified when the number of statellite changes.
     */
    KDBindings::Signal<> numberOfSatellitesChanged;

protected:
    /**
     * Default protected constructor
     */
    IGpsInformationProvider() = default;
};

} // namespace LaptimerCore::Positioning

#endif //!__IGPSINFORMATIONPROVIDER__H__