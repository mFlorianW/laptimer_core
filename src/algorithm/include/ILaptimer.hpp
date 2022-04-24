#ifndef __ILAPTIMER__H__
#define __ILAPTIMER__H__

#include <PositionDateTimeData.hpp>
#include <Timestamp.hpp>
#include <TrackData.hpp>
#include <functional>
#include <kdbindings/property.h>

namespace LaptimerCore::Algorithm
{

class ILaptimer
{
public:
    /**
     * Default desctructor.
     */
    virtual ~ILaptimer() = default;

    /**
     * Sets the Track in the laptimer.
     * The track information is needed to calculate the section and laptime.
     * @param track The new track that is used by the laptimer.
     */
    virtual void setTrack(const Common::TrackData &track);

    /**
     * Update the position in the laptimer.
     * The Position is used in the laptimer to calculate the section and laptime.
     * @param data The new position.
     */
    virtual void updatePositionAndTime(const Common::PositionDateTimeData &data) = 0;

    /**
     * @return Common::Timestamp Gives the last laptime.
     */
    virtual Common::Timestamp getLastLaptime() const = 0;

    /**
     * This signal is emitted when a lap is finished.
     */
    KDBindings::Signal<> lapFinished;

    /**
     * @return Common::Timestamp Gives the last sector time.
     */
    virtual Common::Timestamp getLastSectorTime() const = 0;

    /**
     * This signal is emitted when a lap is finished.
     */
    KDBindings::Signal<> sectorFinished;

    /**
     * This property holds the current active laptime.
     */
    KDBindings::Property<Common::Timestamp> currentLaptime;

    /**
     * This property holds the current active sectiom time.
     */
    KDBindings::Property<Common::Timestamp> currentSectortime;
};

} // namespace LaptimerCore::Algorithm

#endif //!__ILAPTIMER__H__
