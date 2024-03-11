#ifndef ITRACKDATABASEBACKEND_HPP
#define ITRACKDATABASEBACKEND_HPP

#include <TrackData.hpp>

namespace LaptimerCore::Storage
{

class ITrackDatabase
{
public:
    /**
     * Default destructor
     */
    virtual ~ITrackDatabase() = default;

    /**
     * Deleted copy constructor
     */
    ITrackDatabase(ITrackDatabase const& other) = delete;

    /**
     * Deleted copy assignment
     */
    ITrackDatabase& operator=(ITrackDatabase const& other) = delete;

    /**
     * Deleted move constructor
     */
    ITrackDatabase(ITrackDatabase&& other) = delete;

    /**
     * Deleted move assignment
     */
    ITrackDatabase& operator=(ITrackDatabase&& other) = delete;

    /**
     * Gives the number of stored tracks in the database. The number from 0...[TrackCount-1] is the valid index range
     * for track requests and deletions.
     * @return The nummber of stored tracks.
     */
    virtual std::size_t getTrackCount() = 0;

    /**
     * The backend loads all track data.
     * @return true Track data successful loaded.
     * @return false Failed to load track data.
     */
    virtual std::vector<Common::TrackData> getTracks() = 0;

    /**
     * The backend saves the tracks.
     * @param tracks The trackdata that shall be saved.
     * @return true Track data is successfull saved.
     * @return false The track data couldn't be saved.
     */
    virtual bool saveTrack(std::vector<Common::TrackData> const& tracks) = 0;

    /**
     * Deletes all track data.
     * @return true Track data successful deleted.
     * @return false Failed to delete the track data.
     */
    virtual bool deleteTrack(std::size_t trackIndex) = 0;

    /**
     * Deletes all track data.
     * @return true Track data successful deleted.
     * @return false Failed to delete the track data.
     */
    virtual bool deleteAllTracks() = 0;

protected:
    /**
     * Default constructor
     */
    ITrackDatabase() = default;
};

} // namespace LaptimerCore::Storage

#endif //! ITRACKDATABASEBACKEND_HPP
