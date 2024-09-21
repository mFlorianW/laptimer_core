// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef SESSIONDATA_HPP
#define SESSIONDATA_HPP

#include "Date.hpp"
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
     * Alias for the JSON document.
     */
    using JsonDocument = ArduinoJson::StaticJsonDocument<8196>;

    /**
     * Creates an empty invalid SessionData instance.
     */
    SessionData();

    /**
     * Creates SessionData instance
     */
    SessionData(TrackData const& track, Date const& sessionDate, Timestamp const& sessionTime);

    /**
     * Default destructor
     */
    ~SessionData();

    /**
     * Copy constructor for SessionData
     * @param ohter The object to copy from.
     */
    SessionData(SessionData const& other);

    /**
     * The copy assignment operator for SessionData.
     * @param other The object to copy from.
     * @return SessionData& A reference to the copied track.
     */
    SessionData& operator=(SessionData const& other);

    /**
     * Move constructor for SessionData
     * @param other The object to move from.
     */
    SessionData(SessionData&& other);

    /**
     * The move assignment operator for the SessionData.
     * @param other The object to move from.
     * @return SessionData& A reference to the moved track data.
     */
    SessionData& operator=(SessionData&& other);

    /**
     * Gives the date of the session.
     * @return  The date of the session.
     */
    Date getSessionDate() const noexcept;

    /**
     * Gives the time of the session.
     * @return The date of the session.
     */
    Timestamp getSessionTime() const noexcept;

    /**
     * Gives the track of the session.
     * @return The track of the session.
     */
    TrackData const& getTrack() const noexcept;

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
    std::optional<LapData> getLap(std::size_t index) const noexcept;

    /**
     * Gives all laps of the session.
     * @return All laps of the session.
     */
    std::vector<LapData> const& getLaps() const noexcept;

    /**
     * Adds a new lap to the session.
     * @param lapData The lap that shall be added.
     */
    void addLap(LapData const& lap);

    /**
     * Adds the list of laps to the session.
     * @param laps The list of laps that shall be added.
     */
    void addLaps(std::vector<LapData> const& laps);

    /**
     * Equal operator
     * @return true The two objects are the same.
     * @return false The two objects are not the same.
     */
    friend bool operator==(SessionData const& lhs, SessionData const& rhs);

    /**
     * Not Equal operator
     * @return true The two objects are not the same.
     * @return false The two objects are the same.
     */
    friend bool operator!=(SessionData const& lhs, SessionData const& rhs);

private:
    SharedDataPointer<SharedSessionData> mData;
};

} // namespace LaptimerCore::Common

#endif // SESSIONDATA_HPP
