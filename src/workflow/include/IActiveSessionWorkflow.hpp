#ifndef IACTIVESESSIONWORKFLOW_HPP
#define IACTIVESESSIONWORKFLOW_HPP

#include "SessionData.hpp"
#include <kdbindings/property.h>

namespace LaptimerCore::Workflow
{
class IActiveSessionWorkflow
{
public:
    /**
     * Default virtual destructor.
     */
    virtual ~IActiveSessionWorkflow() = default;

    /**
     * Starts the ActiveSessionWorkflow.
     * Without calling start the active workflow session does nothing.
     */
    virtual void startActiveSession() noexcept = 0;

    /**
     * Stops the ActiveSessionWorkflow. No more laps are stored.
     */
    virtual void stopActiveSession() noexcept = 0;

    /**
     * Sets the track that shall be used for the active session.
     * @param track The new track for the session.
     */
    virtual void setTrack(const Common::TrackData &track) noexcept = 0;

    /**
     * Gives the currently active session.
     * Only returns a valid session if startActiveSession is called.
     * @return The currently active session.
     */
    virtual std::optional<Common::SessionData> getSession() const noexcept = 0;

    /**
     * This property holds the current laptime.
     */
    KDBindings::Property<Common::Timestamp> roundTime;

    /**
     * This property holds the current sector time.
     */
    KDBindings::Property<Common::Timestamp> roundSectorTime;

    /**
     * This property holds the current lap count.
     */
    KDBindings::Property<std::size_t> lapCount;

protected:
    /**
     * Default protected constructor.
     */
    IActiveSessionWorkflow() = default;
};

} // namespace LaptimerCore::Workflow

#endif // IACTIVESESSIONWORKFLOW_HPP
