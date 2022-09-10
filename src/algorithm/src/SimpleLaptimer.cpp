#include "SimpleLaptimer.hpp"
#include "DistanceCalculator.hpp"

namespace LaptimerCore::Algorithm
{

class LaptimerStateMachine
{
};

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

    if (mLapState == LapState::WaitingForFirstStart)
    {
        auto startLine = mTrackData.getStartline();
        if (passedPoint(startLine))
        {
            mLapState = LapState::IteratingTrackPoints;
            mCurrentTrackPoint = 0;
            lapStarted.emit();
        }
    }
    else if (mLapState == LapState::IteratingTrackPoints)
    {
        if (passedPoint(mTrackData.getSection(mCurrentTrackPoint)))
        {
            ++mCurrentTrackPoint;
            if (mCurrentTrackPoint > mTrackData.getNumberOfSections())
            {
                mLapState = LapState::WaitingForFinish;
            }
        }
    }
    else if (mLapState == LapState::WaitingForFinish)
    {
        auto finishLine = mTrackData.getStartline();
        if (passedPoint(finishLine))
        {
            // TODO: implement
        }
    }
}

Common::Timestamp SimpleLaptimer::getLastLaptime() const
{
    return {};
}

Common::Timestamp SimpleLaptimer::getLastSectorTime() const
{
    return {};
}

bool SimpleLaptimer::passedPoint(const Common::PositionData &point) const
{
    std::array<float, 4> distances;
    for (size_t i = 0; i < 4 + 1; ++i)
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
