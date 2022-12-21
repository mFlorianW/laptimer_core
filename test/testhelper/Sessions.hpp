#ifndef SESSION_HPP
#define SESSION_HPP

#include "SessionData.hpp"

namespace LaptimerCore::TestHelper
{

class Sessions
{
public:
    const static Common::SessionData TestSession;
    const static Common::SessionData TestSession2;
    const static Common::SessionData TestSession3;

    static Common::SessionData getTestSession3();

    // clang-format off
    static constexpr char TestSessionAsJson[] =
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
    "}";
    // clang-format on
};

} // namespace LaptimerCore::TestHelper

#endif // SESSION_HPP
