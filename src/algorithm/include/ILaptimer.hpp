#ifndef __ILAPTIMER__H__
#define __ILAPTIMER__H__

#include <Laptime.hpp>
#include <PositionData.hpp>
#include <TimeStamp.hpp>
#include <TrackData.hpp>
#include <functional>

namespace LaptimerCore::Algorithm
{

class ILaptimer
{
public:
    /**
     * Alias for a callback when the lap is started.
     */
    using LapStartedCallback = std::function<void()>;

    /**
     * Alias for a callback when the lap is finished.
     */
    using LapFinishedCallback = std::function<void(const Common::Laptime &laptime)>;

    /**
     * Alias for a callback when a section is finished.
     */
    using SectionFinishedCallback = std::function<void(const Common::Timestamp &timestamp)>;

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
    virtual void updatePosition(const Common::PositionData &data) = 0;

    /**
     * @return Common::Timestamp Gives the last section time.
     */
    virtual Common::Timestamp getLastSectionTime() const = 0;

    /**
     * @param sectionIndex The section index where you want to retrieve the time of.
     * @return Common::Timestamp Gives the section for the section given by the index.
     */
    virtual Common::Timestamp getSectionTime(std::uint8_t sectionIndex) const = 0;

    /**
     * @return Common::Timestamp Gives the last laptime.
     */
    virtual Common::Laptime getLastLaptime() const = 0;

    /**
     * Adds a new lap started listener to the laptimer.
     * @param listener The new lap started listener.
     */
    virtual void addLapStartedListener(const LapStartedCallback &listener) = 0;

    /**
     * Adds a new lap finished listener to the laptimer.
     * The listener is called when a laptime is finshed.
     * @param listener The new lap finished listener.
     */
    virtual void addLapFinishedListener(const LapFinishedCallback &listener) = 0;

    /**
     * Adds a new section finished listener to the laptimer.
     * The listener is called when a section is finished.
     * @param listener The new section finished listener.
     */
    virtual void addSectionFinishedListener(const SectionFinishedCallback &listener);
};

} // namespace LaptimerCore::Algorithm

#endif //!__ILAPTIMER__H__