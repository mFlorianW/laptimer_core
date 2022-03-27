#include "LapData.hpp"
#include <ArduinoJson.hpp>

namespace LaptimerCore::Common
{

class SharedLap : public SharedData
{
public:
    Timestamp mLaptime;
    std::vector<Timestamp> mSectorTimes;
};

LapData::LapData()
    : mData{new SharedLap}
{
}

LapData::~LapData() = default;

LapData::LapData(const LapData &other)
    : mData(other.mData)
{
}

LapData &LapData::operator=(const LapData &other)
{
    mData = other.mData;
    return *this;
}

LapData::LapData(LapData &&other)
    : mData{std::move(other.mData)}
{
    other.mData = nullptr;
}

LapData &LapData::operator=(LapData &&other)
{
    LapData moved{std::move(other)};
    std::swap(mData, moved.mData);
    return *this;
}

const Timestamp &LapData::getLaptime() const noexcept
{
    return mData->mLaptime;
}

void LapData::setLaptime(const Timestamp &laptime)
{
    mData->mLaptime = laptime;
}

std::size_t LapData::getSectorTimeCount() const noexcept
{

    return mData->mSectorTimes.size();
}

const std::optional<Timestamp> LapData::getSectorTime(std::size_t index) const noexcept
{
    if (index > mData->mSectorTimes.size())
    {
        return std::nullopt;
    }

    return std::optional<Timestamp>{mData->mSectorTimes[index]};
}

const std::vector<Timestamp> &LapData::getSectorTimes() const noexcept
{
    return mData->mSectorTimes;
}

void LapData::addSectorTime(const Timestamp &sectorTime)
{
    mData->mSectorTimes.push_back(sectorTime);
}

void LapData::addSectorTimes(const std::vector<Timestamp> sectorTimes)
{
    mData->mSectorTimes = sectorTimes;
}

ArduinoJson::DynamicJsonDocument LapData::asJson() const noexcept
{
    constexpr std::size_t staticBuffer = 98;
    const std::size_t jsonBufferSize = staticBuffer + JSON_OBJECT_SIZE(2) + JSON_ARRAY_SIZE(getSectorTimeCount()) +
                                       getSectorTimeCount() * JSON_OBJECT_SIZE(1);
    ArduinoJson::DynamicJsonDocument jsonDoc(jsonBufferSize);
    jsonDoc["laptime"] = getLaptime().asString();

    if (getSectorTimeCount() > 0)
    {
        ArduinoJson::JsonArray jsonSectorTimes = jsonDoc.createNestedArray("sectors");
        for (std::size_t i = 0; i < getSectorTimeCount(); ++i)
        {
            const std::string key = "sector" + std::to_string(i);
            const auto sectorTime = getSectorTime(i);
            auto sectorObject = jsonSectorTimes.createNestedObject();
            if (sectorTime)
            {
                sectorObject[key] = sectorTime.value().asString();
            }
        }
    }

    return jsonDoc;
}

} // namespace LaptimerCore::Common
