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

} // namespace LaptimerCore::Common