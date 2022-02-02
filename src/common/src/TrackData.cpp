#include "TrackData.hpp"

namespace LaptimerCore::Common
{

const std::string &TrackData::getTrackName() const
{
    return mTrackName;
}

void TrackData::setTrackName(const std::string &name)
{
    mTrackName = name;
}

const PositionData &TrackData::getStartline() const
{
    return mStartline;
}

void TrackData::setStartline(const PositionData &startline)
{
    mStartline = startline;
}

const PositionData &TrackData::getFinishline() const
{
    return mFinishline;
}

void TrackData::setFinishline(const PositionData &finishline)
{
    mFinishline = finishline;
}

size_t TrackData::getNumberOfSections() const
{
    return mSections.size();
}

const PositionData &TrackData::getSection(size_t sectionIndex) const
{
    return mSections.at(sectionIndex);
}

const std::vector<PositionData> &TrackData::getSections() const
{
    return mSections;
}

void TrackData::setSections(const std::vector<PositionData> &sections)
{
    mSections = sections;
}

} // namespace LaptimerCore::Common