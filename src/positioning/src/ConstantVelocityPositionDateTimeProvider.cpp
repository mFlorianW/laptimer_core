#include "ConstantVelocityPositionDateTimeProvider.hpp"
#include "UTM.hpp"
#include <fstream>
#include <sys/time.h>

using namespace LaptimerCore::Common;

namespace LaptimerCore::Positioning
{

ConstantVelocityPositionDateTimeProvider::ConstantVelocityPositionDateTimeProvider(
    const std::vector<Common::PositionData> &gpsPositions)
{
    // setup timer
    mTickTimer.setInterval(std::chrono::milliseconds(100));
    mTickTimer.timeout.connect(&ConstantVelocityPositionDateTimeProvider::handleGPSPositionTick, this);

    convertTrackPoints(gpsPositions);
}

void ConstantVelocityPositionDateTimeProvider::setGpsPositions(const std::vector<Common::PositionData> &gpsPositions)
{
    convertTrackPoints(gpsPositions);
}

ConstantVelocityPositionDateTimeProvider::~ConstantVelocityPositionDateTimeProvider() = default;

void ConstantVelocityPositionDateTimeProvider::setVelocityInMeterPerSecond(float speed)
{
    mSpeed = speed;
}

void ConstantVelocityPositionDateTimeProvider::start()
{
    mTickTimer.start();
}

void ConstantVelocityPositionDateTimeProvider::stop()
{
    mTickTimer.stop();
}

void ConstantVelocityPositionDateTimeProvider::convertTrackPoints(const std::vector<Common::PositionData> &gpsPositions)
{
    if (gpsPositions.empty())
    {
        return;
    }

    // convert positions to UTM for easier calculations
    Point point;
    for (const auto &posData : gpsPositions)
    {
        UTM::LLtoUTM(posData.getLatitude(), posData.getLongitude(), point.x, point.y, point.zone);
        mTrackData.push_back(point);
    }

    mTrackDataIt = mTrackData.cbegin();
    mCurrentPosition = *mTrackData.cbegin();
}

void ConstantVelocityPositionDateTimeProvider::handleGPSPositionTick()
{
    if (mTrackData.empty())
    {
        std::cout << "ConstantVelocityPositionDateTimeProvider do nothing: PositionData Empty" << std::endl;
        return;
    }

    if ((mTrackDataIt != mTrackData.cend()) && (mTrackDataIt != mTrackData.begin()))
    {
        auto p0 = *mTrackDataIt;
        // Calculate the direction vector between our current position and the target point
        Point direction{p0.x - mCurrentPosition.x, p0.y - mCurrentPosition.y};

        // Calculate the length of our direction vector
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Normalize direction
        Point normalizedDirection{direction.x / length, direction.y / length};

        // Calculate distance we moved based on speed (meters per second) and elapsed time (seconds)
        auto time = static_cast<float>(mTickTimer.getInterval().count() / 1000.0f);
        Point distanceTraveled{normalizedDirection.x * time * mSpeed, normalizedDirection.y * time * mSpeed};

        // Calculate our new position
        mCurrentPosition.x += distanceTraveled.x;
        mCurrentPosition.y += distanceTraveled.y;

        // If we overran our target point just move on to the next one :)
        direction.x = p0.x - mCurrentPosition.x;
        direction.y = p0.y - mCurrentPosition.y;
        float newLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (newLength > length)
        {
            mTrackDataIt = mTrackDataIt + 2;
            if (mTrackDataIt == mTrackData.cend())
            {
                mTrackDataIt = mTrackData.cbegin();
            }
        }
    }
    else if (mTrackDataIt == mTrackData.cbegin())
    {
        mCurrentPosition = *mTrackDataIt;
        ++mTrackDataIt;
    }
    else
    {
        mTrackDataIt = mTrackData.cbegin();
    }

    auto position = PositionDateTimeData{};
    // set the position
    double lat = 0.0f;
    double longi = 0.0f;
    UTM::UTMtoLL(mCurrentPosition.x, mCurrentPosition.y, mCurrentPosition.zone, lat, longi);
    position.setPosition(PositionData{static_cast<float>(lat), static_cast<float>(longi)});

    // set the time
    const auto timeNow = std::chrono::system_clock::now();
    const auto timeT = std::chrono::system_clock::to_time_t(timeNow);
    const auto time = localtime(&timeT);
    auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(timeNow);
    auto fraction = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - seconds);

    auto timeStamp = Timestamp{};
    timeStamp.setHour(time->tm_hour);
    timeStamp.setMinute(time->tm_min);
    timeStamp.setSecond(time->tm_sec);
    timeStamp.setFractionalOfSecond(fraction.count());
    position.setTime(timeStamp);

    // Set the date.
    auto date = Date{};
    date.setYear(time->tm_year);
    date.setMonth(time->tm_mon);
    date.setDay(time->tm_mday);
    position.setDate(date);

    positionTimeData.set(position);
}

} // namespace LaptimerCore::Positioning
