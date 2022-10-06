#ifndef FILEBASEDPOSITIONDATETIMEPROVIDER_HPP
#define FILEBASEDPOSITIONDATETIMEPROVIDER_HPP

#include "IPositionDateTimeProvider.hpp"
#include <Timer.hpp>
#include <filesystem>

namespace LaptimerCore::Positioning
{

/**
 * This PositionDateTimeProvider replays a list of GPS positions at a 10Hz frequency. The replayed
 * positions are based on the provided list. Positions are automatically interpolated when the two
 * positions are to far of each other. The interpolated position is based on set veclocity.
 */
class ConstantVelocityPositionDateTimeProvider final : public IPositionDateTimeProvider
{
public:
    /**
     * Creates an instance of the FileBasedPositionDateTimeProvider.
     * @param gpsPositions The GPS position list that is used for the replay.
     */
    ConstantVelocityPositionDateTimeProvider(const std::vector<Common::PositionData> &gpsPositions);

    /**
     * Empty default destructor
     */
    ~ConstantVelocityPositionDateTimeProvider() override;

    /**
     * Sets the speed for the GPS position updates.
     * It's only possible to update the speed when the provider is not running.
     * @param speed The speed in meter per second.
     */
    void setVelocityInMeterPerSecond(float velocity);

    /**
     * Starts the GPS position date time provider.
     */
    void start();

    /**
     * Stops the GPS position date time provider.
     */
    void stop();

private:
    void handleGPSPositionTick();

private:
    struct Point
    {
        double x = 0.0f;
        double y = 0.0f;
        char zone[3] = {0};
    };

    float mSpeed;
    Common::Timer mTickTimer;
    std::vector<Point> mTrackData;
    std::vector<Point>::const_iterator mTrackDataIt;
    Point mCurrentPosition;
};

} // namespace LaptimerCore::Positioning

#endif // FILEBASEDPOSITIONDATETIMEPROVIDER_HPP
