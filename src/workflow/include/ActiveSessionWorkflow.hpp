#ifndef ACTIVESESSIONWORKFLOW_HPP
#define ACTIVESESSIONWORKFLOW_HPP

#include "IActiveSessionWorkflow.hpp"
#include <ILaptimer.hpp>
#include <IPositionDateTimeProvider.hpp>
#include <ISessionDatabase.hpp>

namespace LaptimerCore::Workflow
{
class ActiveSessionWorkflow : public IActiveSessionWorkflow
{
public:
    /**
     * Creates an instance of the ActiveSessionWorkflow
     * @param timeDateProvider The date and time information provider to get the latest time date informations.
     * @param laptimer The laptimer that is used to get notified about new laps and sectors.
     * @param database The session database that shall be used to store the data.
     */
    ActiveSessionWorkflow(Positioning::IPositionDateTimeProvider &positionDateTimeProvider,
                          Algorithm::ILaptimer &laptimer,
                          Session::ISessionDatabase &database);

    /**
     * @copydoc IActiveSessionWorkflow::startActiveSession()
     */
    void startActiveSession() noexcept override;

    /**
     * @copydoc IActiveSessionWorkflow::stopActiveSession()
     */
    void stopActiveSession() noexcept override;

    /**
     * @copydoc IActiveSessionWorkflow::setTraco()
     */
    void setTrack(const Common::TrackData &track) noexcept override;

    /**
     * @copydoc IActiveSessionWorkflow::getActiveSession()
     */
    std::optional<Common::SessionData> getSession() const noexcept override;

private:
    void onLapFinished();
    void onSectorFinished();
    void onCurrentLaptimeChanged();
    void onCurrentSectorTimeChanged();

private:
    Positioning::IPositionDateTimeProvider &mDateTimeProvider;
    Algorithm::ILaptimer &mLaptimer;
    Session::ISessionDatabase &mDatabase;
    std::optional<Common::SessionData> mSession;
    Common::TrackData mTrack;
    Common::LapData mCurrentLap;
};

} // namespace LaptimerCore::Workflow

#endif // ACTIVESESSIONWORKFLOW_HPP
