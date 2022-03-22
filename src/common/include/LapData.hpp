#ifndef LAP_HPP
#define LAP_HPP

#include "SharedDataPointer.hpp"
#include "Timestamp.hpp"
#include <ArduinoJson.hpp>
#include <optional>
#include <vector>

namespace LaptimerCore::Common
{
class SharedLap;

/**
 * A lap is representation of lap and is part of session.
 * The lap has a laptime and depending on the track amount sector times.
 */
class LapData final
{
public:
    /**
     * Creates an empty lap
     */
    LapData();

    /**
     * Default destructor
     */
    ~LapData();

    /**
     * Copy constructor for LapData
     * @param ohter The object to copy from.
     */
    LapData(const LapData &ohter);

    /**
     * The copy assignment operator for LapData.
     * @param other The object to copy from.
     * @return LapData& A reference to the copied track.
     */
    LapData &operator=(const LapData &other);

    /**
     * Move constructor for LapData
     * @param other The object to move from.
     */
    LapData(LapData &&other);

    /**
     * The move assignment operator for the LapData.
     * @param other The object to move from.
     * @return LapData& A reference to the moved track data.
     */
    LapData &operator=(LapData &&other);

    /**
     * Gives the overall laptime.
     * @return The overall laptime.
     */
    const Timestamp &getLaptime() const noexcept;

    /**
     * Sets the overall laptime.
     * @param laptime The new overall laptime.
     */
    void setLaptime(const Timestamp &laptime);

    /**
     * Gives the amount of sectors.
     * @return The number of sectors.
     */
    std::size_t getSectorTimeCount() const noexcept;

    /**
     * Gives a sector time for a specific setctor.
     * If the index is bigger than the lap sector count a nullopt is returned.
     * @param index The index of the sector.
     * @return The sector time for the index.
     */
    const std::optional<Timestamp> getSectorTime(std::size_t index) const noexcept;

    /**
     * Gives a list of all sector times.
     * @return A list with all sector times.
     */
    const std::vector<Timestamp> &getSectorTimes() const noexcept;

    /**
     * Adds a new sector time to the lap.
     * The order to this function calls define the sector ordering.
     * @param sectorTime The sector that shall be added.
     */
    void addSectorTime(const Timestamp &sectorTime);

    /**
     * Adds a list of sector times to the lap.
     * The order of the list defines the ordering of the sectors.
     * @param sectorTimes The list of sector times.
     */
    void addSectorTimes(const std::vector<Timestamp> sectorTimes);

    /**
     * Creates
     * @return
     */
    ArduinoJson::DynamicJsonDocument serialize() const noexcept;

private:
    SharedDataPointer<SharedLap> mData;
};

} // namespace LaptimerCore::Common
#endif // LAP_HPP
