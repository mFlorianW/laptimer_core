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

    friend bool operator==(SharedSessionData const& lhs, SharedSessionData const& rhs)
    {
        // clang-format off
        return ((lhs.mSessionDate) == (rhs.mSessionDate) &&
                (lhs.mSessionTime) == (rhs.mSessionTime) &&
                (lhs.mSessionTrack) == (rhs.mSessionTrack) &&
                (lhs.mLaps) == (rhs.mLaps));
        // clang-format on
    }
};

SessionData::SessionData()
    : mData{new SharedSessionData}
{
}

SessionData::SessionData(TrackData const& track, Date const& sessionDate, Timestamp const& sessionTime)
    : mData{new SharedSessionData}
{
    mData->mSessionTrack = track;
    mData->mSessionTime = sessionTime;
    mData->mSessionDate = sessionDate;
}

SessionData::~SessionData() = default;

SessionData::SessionData(SessionData const& other)
    : mData(other.mData)
{
}

SessionData& SessionData::operator=(SessionData const& other)
{
    mData = other.mData;
    return *this;
}

Date SessionData::getSessionDate() const noexcept
{
    return mData->mSessionDate;
}

SessionData::SessionData(SessionData&& other)
    : mData{std::move(other.mData)}
{
}

SessionData& SessionData::operator=(SessionData&& other)
{
    SessionData moved{std::move(other)};
    std::swap(moved.mData, mData);
    return *this;
}

Timestamp SessionData::getSessionTime() const noexcept
{
    return mData->mSessionTime;
}

TrackData const& SessionData::getTrack() const noexcept
{
    return mData->mSessionTrack;
}

std::size_t SessionData::getNumberOfLaps() const noexcept
{
    return mData->mLaps.size();
}

std::optional<LapData> SessionData::getLap(std::size_t index) const noexcept
{
    if (index > mData->mLaps.size()) {
        return std::nullopt;
    }

    return {mData->mLaps.at(index)};
}

std::vector<LapData> const& SessionData::getLaps() const noexcept
{
    return mData->mLaps;
}

void SessionData::addLap(LapData const& lap)
{
    mData->mLaps.push_back(lap);
}

void SessionData::addLaps(std::vector<LapData> const& laps)
{
    for (auto const& lap : laps) {
        mData->mLaps.push_back(lap);
    }
}

bool operator==(SessionData const& lhs, SessionData const& rhs)
{
    return lhs.mData == rhs.mData || *lhs.mData == *rhs.mData;
}

bool operator!=(SessionData const& lhs, SessionData const& rhs)
{
    return !(lhs == rhs);
}

} // namespace LaptimerCore::Common
