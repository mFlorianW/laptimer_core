#ifndef SESSIONDATA_HPP
#define SESSIONDATA_HPP

#include "LapData.hpp"
#include "SharedDataPointer.hpp"
#include "TrackData.hpp"

namespace LaptimerCore::Common
{

class SharedSessionData;
class SessionData final
{
public:
    /**
     * Creates SessionData instance
     */
    SessionData(const TrackData &track, const Timestamp &sessionDate);

    /**
     * Default destructor
     */
    ~SessionData();

    /**
     * Copy constructor for SessionData
     * @param ohter The object to copy from.
     */
    SessionData(const SessionData &other);

    /**
     * The copy assignment operator for SessionData.
     * @param other The object to copy from.
     * @return SessionData& A reference to the copied track.
     */
    SessionData &operator=(const SessionData &other);

    /**
     * Move constructor for SessionData
     * @param other The object to move from.
     */
    SessionData(SessionData &&other);

    /**
     * The move assignment operator for the SessionData.
     * @param other The object to move from.
     * @return SessionData& A reference to the moved track data.
     */
    SessionData &operator=(SessionData &&other);

    /**
     * Gives the date of the session.
     * @return The date of the session.
     */
    Timestamp getSessionDate() const noexcept;

    /**
     * Gives the track of the session.
     * @return The track of the session.
     */
    const TrackData &getTrack() const noexcept;

    /**
     * Gives the number of recored laps of the session.
     * @return
     */
    std::size_t getNumberOfLaps() const noexcept;

    /**
     * Gives the lap for the given index only for a valid index.
     * @param index The index of the lap.
     * @return Gives the lap for the given index or a nullopt if the index is not valid.
     */
    std::optional<LapData> getLap(std::size_t index);

    /**
     * Gives all laps of the session.
     * @return All laps of the session.
     */
    const std::vector<LapData> &getLaps() const noexcept;

    /**
     * Adds a new lap to the session.
     * @param lapData The lap that shall be added.
     */
    void addLap(const LapData &lap);

private:
    SharedDataPointer<SharedSessionData> mData;
};

} // namespace LaptimerCore::Common

#endif // SESSIONDATA_HPP
