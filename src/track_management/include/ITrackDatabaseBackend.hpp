#ifndef __ITRACKDATABASEBACKEND__H__
#define __ITRACKDATABASEBACKEND__H__

#include <TrackData.hpp>

namespace LaptimerCore::TrackManagement
{

class ITrackDatabaseBackend
{
public:
    virtual ~ITrackDatabaseBackend() = default;

    /**
     * The backend loads all track data.
     * @return true Track data successful loaded.
     * @return false Failed to load track data.
     */
    virtual bool loadTrackData() = 0;

    /**
     * The backend saves the tracks.
     * @param tracks The trackdata that shall be saved.
     * @return true Track data is successfull saved.
     * @return false The track data couldn't be saved.
     */
    virtual bool saveTrackData(const std::vector<TrackData> &tracks) = 0;

    /**
     * Deletes all track data.
     * @return true Track data successful deleted.
     * @return false Failed to delete the track data.
     */
    virtual bool deleteTrackData() = 0;
};

} // namespace LaptimerCore::TrackManagement

#endif //!__ITRACKDATABASEBACKEND__H__