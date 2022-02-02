#ifndef __TRACKDATA__H__
#define __TRACKDATA__H__

#include "PositionData.hpp"
#include <string>
#include <vector>

namespace LaptimerCore::Common
{

/**
 * The track data class contains the data of a real racetrack.
 */
class TrackData final
{
public:
    /**
     * Gives the track name.
     * @return const std::string& The track name.
     */
    const std::string &getTrackName() const;

    /**
     * Sets the new track name.
     * @param name The new name of the track.
     */
    void setTrackName(const std::string &name);

    /**
     * Gives the position data of the start line.
     * @return const PositionData& The position of the start line.
     */
    const PositionData &getStartline() const;

    /**
     * Set a new position for the start line.
     * @param startLine The new position for the start line.
     */
    void setStartline(const PositionData &startLine);

    /**
     * Gives the position of the finish line.
     * @return const PositionData&
     */
    const PositionData &getFinishline() const;

    /**
     * Sets a new position for the finish line.
     * @param finishLine The new position of the finish line.
     */
    void setFinishline(const PositionData &finishline);

    /**
     * Gives the number of sections of the race track.
     * @return size_t The number of sections.
     */
    size_t getNumberOfSections() const;

    /**
     * Gives the position of a section given by the index.
     * If the index is bigger than the section count a default constructed PositionData will be returned.
     * @param sectionIndex The section index.
     * @return const PositionData& The position data of the section.
     */
    const PositionData &getSection(size_t sectionIndex) const;

    /**
     * Gives a list of all sections of the track.
     * @return const std::vector<PositionData>& A list with all sections of the track.
     */
    const std::vector<PositionData> &getSections() const;

    /**
     * Sets the sections for the race track.
     * The sections are consumed and the passed vector is not longer available after it.
     * @param sections The new sections of the track.
     */
    void setSections(const std::vector<PositionData> &sections);

private:
    std::string mTrackName;
    PositionData mFinishline;
    PositionData mStartline;
    std::vector<PositionData> mSections;
};

} // namespace LaptimerCore::Common

#endif //!__TRACKDATA__H__