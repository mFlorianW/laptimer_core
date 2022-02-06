#ifndef __POSITIONDATA__H__
#define __POSITIONDATA__H__

#include "SharedDataPointer.hpp"

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

private:
    SharedDataPointer<SharedPositionData> mData;
};

} // namespace LaptimerCore::Common

#endif //!__POSITIONDATA__H__
