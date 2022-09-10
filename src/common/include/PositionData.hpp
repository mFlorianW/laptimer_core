#ifndef __POSITIONDATA__H__
#define __POSITIONDATA__H__

#include "SharedDataPointer.hpp"
#include <ArduinoJson.hpp>

namespace LaptimerCore::Common
{

class SharedPositionData;
class PositionData final
{
public:
    /**
     * Creates an instance of PositionData.
     */
    PositionData();

    /**
     * Creates a PositionData instance with given latitude and longitude.
     * @param latitude The latitude of the PositionData.
     * @param longitude The longitude of the PositionData.
     */
    PositionData(float latitude, float longitude);

    /**
     * Default destructor.
     */
    ~PositionData();

    /**
     * Copy constructor for PositionData.
     * @param other The object to copy from.
     */
    PositionData(const PositionData &other);

    /**
     * Copy assignment operator for PositionData.
     * @param other The object to copy from.
     * @return PositionData& A reference to the copied instance.
     */
    PositionData &operator=(const PositionData &other);

    /**
     * The move constructor for PositionData.
     * @param other The object to move from.
     */
    PositionData(PositionData &&other);

    /**
     * The move assignment operator for PositionData.
     * @param other The object to move from.
     * @return PositionData& A reference of the moved instance.
     */
    PositionData &operator=(PositionData &&other);

    /**
     * Gives the latitude.
     * @return float The latitude.
     */
    float getLatitude() const;

    /**
     * Sets a new latitude value.
     * @param latitude The Latitude value.
     */
    void setLatitude(float latitude);

    /**
     * Gives the longitude.
     * @return float The longitude.
     */
    float getLongitude() const;

    /**
     * Sets a new longitude value.
     * @param longitude The new longitude value.
     */
    void setLongitude(float longitude);

    /**
     * Equal operator
     * @return true The two objects are the same.
     * @return false The two objects are not the same.
     */
    friend bool operator==(const PositionData &lhs, const PositionData &rhs);

    /**
     * Not Equal operator
     * @return true The two objects are not the same.
     * @return false The two objects are the same.
     */
    friend bool operator!=(const PositionData &lhs, const PositionData &rhs);

private:
    SharedDataPointer<SharedPositionData> mData;
};

} // namespace LaptimerCore::Common

#endif //!__POSITIONDATA__H__
