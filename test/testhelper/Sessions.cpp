#include "Sessions.hpp"
#include "Tracks.hpp"

using namespace LaptimerCore::Common;

namespace LaptimerCore::TestHelper
{

SessionData createSession()
{
    Tracks::init();

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

    auto session = SessionData{Tracks::OscherslebenTrack, sessionDate, sessionTime};
    session.addLap(lap);

    return session;
}

SessionData createSession2()
{
    Tracks::init();

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

    auto session = SessionData{Tracks::OscherslebenTrack, sessionDate, sessionTime};
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

    auto session = SessionData{Tracks::OscherslebenTrack2, sessionDate, sessionTime};
    session.addLap(lap);
    session.addLap(lap);

    return session;
}

const SessionData Sessions::TestSession{createSession()};
const SessionData Sessions::TestSession2{createSession2()};
const SessionData Sessions::TestSession3{createSession3()};

SessionData Sessions::getTestSession3()
{
    return createSession3();
}

} // namespace LaptimerCore::TestHelper
