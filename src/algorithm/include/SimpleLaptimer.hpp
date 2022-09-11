#ifndef SIMPLELAPTIMER_HPP
#define SIMPLELAPTIMER_HPP

#include "ILaptimer.hpp"
#include <deque>

namespace LaptimerCore::Algorithm
{

class SimpleLaptimer final : public ILaptimer
{
public:
    /**
     * Default constructor
     */
    SimpleLaptimer() = default;

    /**
     * Default destructor
     */
    ~SimpleLaptimer() = default;

    /**
     * @copydoc ILaptimer::setTrack(const Common::TrackData &track)
     */
    void setTrack(const Common::TrackData &track) override;

    /**
     * @copydoc updatePositionAndTime(const Common::PositionDateTimeData &data)
     */
    void updatePositionAndTime(const Common::PositionDateTimeData &data) override;

    /**
     * @copydoc ILaptimer::getLastLaptime()
     */
    Common::Timestamp getLastLaptime() const override;

    /**
     * @copydoc ILaptimer::getLastLaptime()
     */
    Common::Timestamp getLastSectorTime() const override;

private:
    /**
     * Checks if the last 4 positions stored in mCurrentPoints passed the point specified.
     * @param point The point the shall be checked against the last 4 known positions.
     * @return True if the point specified was passed, False otherwise.
     */
    bool passedPoint(const Common::PositionData &point) const;

private:
    Common::TrackData mTrackData;
    size_t mCurrentTrackPoint{0};

    /* This double ended que contains the last 4 track points. The point at position 0 is the latest one
    and the point at position 3 is the oldest respectively. */
    std::deque<Common::PositionData> mCurrentPoints;

    enum LapState
    {
        WaitingForFirstStart,
        IteratingTrackPoints,
        WaitingForFinish
    };

    LapState mLapState{WaitingForFirstStart};
    Common::Timestamp mLapStartedTimeStamp;
    Common::Timestamp mLastLapTime;
};

} // namespace LaptimerCore::Algorithm

#endif // SIMPLELAPTIMER_HPP
