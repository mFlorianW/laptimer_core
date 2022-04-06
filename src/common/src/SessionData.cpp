#include "SessionData.hpp"
#include <ArduinoJson.h>

namespace LaptimerCore::Common
{

class SharedSessionData : public SharedData
{
public:
    Date mSessionDate;
    Timestamp mSessionTime;
    TrackData mSessionTrack;
    std::vector<LapData> mLaps;
};

SessionData::SessionData(const TrackData &track, const Date &sessionDate, const Timestamp &sessionTime)
    : mData{new SharedSessionData}
{
    mData->mSessionTrack = track;
    mData->mSessionTime = sessionTime;
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

Date SessionData::getSessionDate() const noexcept
{
    return mData->mSessionDate;
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

Timestamp SessionData::getSessionTime() const noexcept
{
    return mData->mSessionTime;
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

bool operator==(const SessionData &lhs, const SessionData &rhs)
{
    return lhs.mData == rhs.mData;
}

bool operator!=(const SessionData &lhs, const SessionData &rhs)
{
    return lhs.mData != rhs.mData;
}

} // namespace LaptimerCore::Common
