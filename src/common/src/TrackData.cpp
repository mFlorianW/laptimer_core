#include "TrackData.hpp"

namespace LaptimerCore::Common
{

class SharedTrackData : public SharedData
{
public:
    std::string mTrackName;
    PositionData mFinishline;
    PositionData mStartline;
    std::vector<PositionData> mSections;
};

TrackData::TrackData()
    : mData{new SharedTrackData{}}
{
}

TrackData::~TrackData() = default;

TrackData::TrackData(const TrackData &ohter)
    : mData(ohter.mData)
{
}

TrackData &TrackData::operator=(const TrackData &other)
{
    mData = other.mData;
    return *this;
}

TrackData::TrackData(TrackData &&other)
    : mData{std::move(other.mData)}
{
    other.mData = nullptr;
}

TrackData &TrackData::operator=(TrackData &&other)
{
    TrackData moved{std::move(other)};
    std::swap(mData, moved.mData);
    return *this;
}

const std::string &TrackData::getTrackName() const
{
    return mData->mTrackName;
}

void TrackData::setTrackName(const std::string &name)
{
    mData->mTrackName = name;
}

const PositionData &TrackData::getStartline() const
{
    return mData->mStartline;
}

void TrackData::setStartline(const PositionData &startline)
{
    mData->mStartline = startline;
}

const PositionData &TrackData::getFinishline() const
{
    return mData->mFinishline;
}

void TrackData::setFinishline(const PositionData &finishline)
{
    mData->mFinishline = finishline;
}

size_t TrackData::getNumberOfSections() const
{
    return mData->mSections.size();
}

const PositionData &TrackData::getSection(size_t sectionIndex) const
{
    return mData->mSections.at(sectionIndex);
}

const std::vector<PositionData> &TrackData::getSections() const
{
    return mData->mSections;
}

void TrackData::setSections(const std::vector<PositionData> &sections)
{
    mData->mSections = sections;
}

ArduinoJson::DynamicJsonDocument TrackData::asJson() const noexcept
{
    auto jsonObject = ArduinoJson::DynamicJsonDocument{1024};

    jsonObject["name"] = getTrackName();
    jsonObject["startline"] = getStartline().asJson();
    jsonObject["finishline"] = getFinishline().asJson();

    if (getNumberOfSections() > 0)
    {
        auto sectorList = jsonObject.createNestedArray("sectors");
        for (std::size_t i = 0; i < getNumberOfSections(); ++i)
        {
            sectorList.add(getSection(i).asJson());
        }
    }

    return jsonObject;
}

bool operator==(const TrackData &lhs, const TrackData &rhs)
{
    return lhs.mData == rhs.mData;
}

bool operator!=(const TrackData &lhs, const TrackData &rhs)
{
    return lhs.mData != rhs.mData;
}

} // namespace LaptimerCore::Common
