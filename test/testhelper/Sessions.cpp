#include "Sessions.hpp"
#include "Tracks.hpp"
#include <array>

using namespace LaptimerCore::Common;

namespace LaptimerCore::TestHelper::Sessions
{

SessionData createSession()
{
    Date sessionDate;
    sessionDate.setYear(1970);
    sessionDate.setMonth(1);
    sessionDate.setDay(1);
    Timestamp sessionTime;
    sessionTime.setHour(13);

    Timestamp sectorTime;
    sectorTime.setFractionalOfSecond(144);
    sectorTime.setSecond(25);

    LapData lap;
    lap.addSectorTime(sectorTime);
    lap.addSectorTime(sectorTime);
    lap.addSectorTime(sectorTime);
    lap.addSectorTime(sectorTime);

    auto session = SessionData{Tracks::getOscherslebenTrack(), sessionDate, sessionTime};
    session.addLap(lap);

    return session;
}

SessionData createSession2()
{
    Date sessionDate;
    sessionDate.setYear(1970);
    sessionDate.setMonth(2);
    sessionDate.setDay(1);
    Timestamp sessionTime;
    sessionTime.setHour(13);

    Timestamp sectorTime;
    sectorTime.setFractionalOfSecond(144);
    sectorTime.setSecond(25);

    LapData lap;
    lap.addSectorTime(sectorTime);
    lap.addSectorTime(sectorTime);
    lap.addSectorTime(sectorTime);
    lap.addSectorTime(sectorTime);

    auto session = SessionData{Tracks::getOscherslebenTrack(), sessionDate, sessionTime};
    session.addLap(lap);

    return session;
}

SessionData createSession3()
{
    Date sessionDate;
    sessionDate.setYear(1970);
    sessionDate.setMonth(2);
    sessionDate.setDay(1);
    Timestamp sessionTime;
    sessionTime.setHour(13);

    Timestamp sectorTime;
    sectorTime.setFractionalOfSecond(144);
    sectorTime.setSecond(25);

    LapData lap;
    lap.addSectorTime(sectorTime);
    lap.addSectorTime(sectorTime);
    lap.addSectorTime(sectorTime);
    lap.addSectorTime(sectorTime);

    auto session = SessionData{Tracks::getOscherslebenTrack2(), sessionDate, sessionTime};
    session.addLap(lap);
    session.addLap(lap);

    return session;
}

SessionData getTestSession3()
{
    return createSession3();
}

SessionData getTestSession()
{
    return createSession();
}

SessionData getTestSession2()
{
    return createSession2();
}

const char *getTestSessionAsJson()
{
    // clang-format off
    static constexpr std::array<char, 392> TestSessionAsJson = {
        "{"
            "\"date\":\"01.01.1970\","
            "\"time\":\"13:00:00.000\","
            "\"track\":{"
                "\"name\":\"Oschersleben\","
                "\"startline\":{"
                    "\"latitude\":\"52.025833\","
                    "\"longitude\":\"11.279166\""
                "},"
            "\"finishline\":{"
                    "\"latitude\":\"52.025833\","
                    "\"longitude\":\"11.279166\""
            "},"
            "\"sectors\":["
                "{"
                    "\"latitude\":\"52.025833\","
                    "\"longitude\":\"11.279166\""
                "},"
                "{"
                    "\"latitude\":\"52.025833\","
                    "\"longitude\":\"11.279166\""
                "}"
            "]"
            "},"
            "\"laps\":["
                "{"
                "\"sectors\":["
                        "\"00:00:25.144\","
                        "\"00:00:25.144\","
                        "\"00:00:25.144\","
                        "\"00:00:25.144\""
                    "]"
                "}"
            "]"
        "}"
    };
    // clang-format on
    return &TestSessionAsJson[0];
}

} // namespace LaptimerCore::TestHelper::Sessions
