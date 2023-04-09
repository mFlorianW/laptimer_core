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
     * Alias for the JsonDocument
     */
    using JsonDocument = ArduinoJson::StaticJsonDocument<1024>;

    /**
     * Creates an empty lap
     */
    LapData();

    /**
     * Creates an instance of lapdata
     * @param laptime The time which is used a laptime.
     */
    explicit LapData(const Timestamp &laptime);

    /**
     * Constructs LapData instance with
     * @param sectorTimes The array of sector times.
     */
    explicit LapData(const std::vector<Timestamp> &sectorTimes);

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
    LapData(LapData &&other) noexcept;

    /**
     * The move assignment operator for the LapData.
     * @param other The object to move from.
     * @return LapData& A reference to the moved track data.
     */
    LapData &operator=(LapData &&other) noexcept;

    /**
     * Gives the overall laptime.
     * The laptime is the accmulation overall sector times and is only valid
     * if all sector of the lap are added.
     * @return The overall laptime.
     */
    [[nodiscard]] Timestamp getLaptime() const noexcept;

    /**
     * Gives the amount of sectors.
     * @return The number of sectors.
     */
    [[nodiscard]] std::size_t getSectorTimeCount() const noexcept;

    /**
     * Gives a sector time for a specific sector.
     * If the index is bigger than the lap sector count a nullopt is returned.
     * @param index The index of the sector.
     * @return The sector time for the index.
     */
    [[nodiscard]] std::optional<Timestamp> getSectorTime(std::size_t index) const noexcept;

    /**
     * Gives a list of all sector times.
     * @return A list with all sector times.
     */
    [[nodiscard]] const std::vector<Timestamp> &getSectorTimes() const noexcept;

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
    void addSectorTimes(const std::vector<Timestamp> &sectorTimes);

    /**
     * Equal operator
     * @return true The two objects are the same.
     * @return false The two objects are not the same.
     */
    friend bool operator==(const LapData &lhs, const LapData &rhs);

    /**
     * Not Equal operator
     * @return true The two objects are not the same.
     * @return false The two objects are the same.
     */
    friend bool operator!=(const LapData &lhs, const LapData &rhs);

private:
    SharedDataPointer<SharedLap> mData;
};

} // namespace LaptimerCore::Common
#endif // LAP_HPP
