#ifndef SESSION_HPP
#define SESSION_HPP

#include "SessionData.hpp"

namespace LaptimerCore::TestHelper::Sessions
{
Common::SessionData getTestSession();
Common::SessionData getTestSession2();
Common::SessionData getTestSession3();
Common::SessionData getTestSession4();
char const* getTestSessionAsJson();

} // namespace LaptimerCore::TestHelper::Sessions

#endif // SESSION_HPP
