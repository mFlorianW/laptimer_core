#include "SimpleLaptimer.hpp"
#include "DistanceCalculator.hpp"

using namespace LaptimerCore::Common;

namespace LaptimerCore::Algorithm
{

void SimpleLaptimer::setTrack(const Common::TrackData &track)
{
    mTrackData = track;
}

void SimpleLaptimer::updatePositionAndTime(const Common::PositionDateTimeData &data)
{
    mCurrentPoints.push_front(data.getPosition());
    if (mCurrentPoints.size() > 4)
    {
        mCurrentPoints.pop_back();
    }
    else if (mCurrentPoints.size() < 4)
    {
        return;
    }

    // Update currentLaptime
    if (mLapState != LapState::WaitingForFirstStart)
    {
        const auto lapTime = data.getTime() - mLapStartedTimestamp;
        currentLaptime.set(lapTime);

        const auto sectorTime = data.getTime() - mSectorStartedTimestamp;
        currentSectorTime.set(sectorTime);
    }

    if (mLapState == LapState::WaitingForFirstStart)
    {
        const auto startLine = mTrackData.getStartline();
        if (passedPoint(startLine))
        {
            mLapState =
                (mTrackData.getNumberOfSections() > 0) ? LapState::IteratingTrackPoints : LapState::WaitingForFinish;
            mCurrentTrackPoint = 0;
            currentLaptime.set(Timestamp{"00:00:00.000"});
            currentSectorTime.set(Timestamp{"00:00:00.000"});
            mLapStartedTimestamp = data.getTime();
            mSectorStartedTimestamp = data.getTime();
            lapStarted.emit();
        }
    }
    else if (mLapState == LapState::IteratingTrackPoints)
    {
        if (passedPoint(mTrackData.getSection(mCurrentTrackPoint)))
        {
            ++mCurrentTrackPoint;
            if (mCurrentTrackPoint >= mTrackData.getNumberOfSections())
            {
                mLapState = LapState::WaitingForFinish;
            }
            mLastSectorTime = currentSectorTime.get();
            mSectorStartedTimestamp = data.getTime();
            currentSectorTime.set(Timestamp{"00:00:00.000"});
            sectorFinished.emit();
        }
    }
    else if (mLapState == LapState::WaitingForFinish)
    {
        const auto finishLine = mTrackData.getFinishline();
        if (passedPoint(finishLine))
        {
            mLastLapTime = currentLaptime.get();
            mLastSectorTime = currentSectorTime.get();
            mLapStartedTimestamp = data.getTime();
            mSectorStartedTimestamp = data.getTime();
            currentLaptime.set(Timestamp{"00:00:00.000"});
            currentSectorTime.set(Timestamp{"00:00:00.000"});

            // TODO: Only works with with a circuit. Additional check is needed in the future when the finish line
            // and start line is not the same.
            if (mTrackData.getNumberOfSections() > 0)
            {
                mCurrentTrackPoint = 0;
                mLapState = LapState::IteratingTrackPoints;
            }
            else
            {
                mCurrentPoints.clear();
            }

            sectorFinished.emit();
            lapFinished.emit();
            lapStarted.emit();
        }
    }
}

Common::Timestamp SimpleLaptimer::getLastLaptime() const
{
    return mLastLapTime;
}

Common::Timestamp SimpleLaptimer::getLastSectorTime() const
{
    return mLastSectorTime;
}

bool SimpleLaptimer::passedPoint(const Common::PositionData &point) const
{
    constexpr std::uint8_t range = 50;
    bool pointsInRange = std::all_of(mCurrentPoints.cbegin(), mCurrentPoints.cend(), [=](Common::PositionData pos) {
        return DistanceCalculator::calculateDistance(pos, point) <= range;
    });

    if (!pointsInRange)
    {
        return false;
    }

    std::array<float, 4> distances;
    for (size_t i = 0; i < 4; ++i)
    {
        distances[i] = DistanceCalculator::calculateDistance(mCurrentPoints[i], point);
    }

    if ((distances[0] > distances[1]) && (distances[1] < distances[2]) && (distances[2] < distances[3]))
    {
        return true;
    }
    else if ((distances[0] > distances[1]) && (distances[1] > distances[2]) && (distances[2] < distances[3]))
    {
        return true;
    }

    return false;
}

} // namespace LaptimerCore::Algorithm
