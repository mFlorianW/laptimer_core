#include "SessionData.hpp"

namespace LaptimerCore::Common
{

class SharedSessionData : public SharedData
{
public:
    Timestamp mSessionDate;
    TrackData mSessionTrack;
    std::vector<LapData> mLaps;
};

SessionData::SessionData(const TrackData &track, const Timestamp &sessionDate)
    : mData(new SharedSessionData{})
{
    mData->mSessionTrack = track;
    mData->mSessionDate = sessionDate;
}

SessionData::~SessionData() = default;

SessionData::SessionData(const SessionData &other)
    : mData(other.mData)
{
}

SessionData &SessionData::operator=(const SessionData &other)
{
    mData = other.mData;
    return *this;
}

SessionData::SessionData(SessionData &&other)
    : mData{std::move(other.mData)}
{
}

SessionData &SessionData::operator=(SessionData &&other)
{
    SessionData moved{std::move(other)};
    std::swap(moved.mData, mData);
    return *this;
}

Timestamp SessionData::getSessionDate() const noexcept
{
    return mData->mSessionDate;
}

const TrackData &SessionData::getTrack() const noexcept
{
    return mData->mSessionTrack;
}

std::size_t SessionData::getNumberOfLaps() const noexcept
{
    return mData->mLaps.size();
}

std::optional<LapData> SessionData::getLap(std::size_t index)
{
    if (index > mData->mLaps.size())
    {
        return std::nullopt;
    }

    return {mData->mLaps.at(index)};
}

const std::vector<LapData> &SessionData::getLaps() const noexcept
{
    return mData->mLaps;
}

void SessionData::addLap(const LapData &lap)
{
    mData->mLaps.push_back(lap);
}

} // namespace LaptimerCore::Common
