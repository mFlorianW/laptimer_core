#ifndef __POSITIONS__H__
#define __POSITIONS__H__

#include "PositionData.hpp"

namespace LaptimerCore::Test::Dummy
{

class Positions
{
public:
    static void init();

    static Common::PositionData OscherslebenPosition;
};

} // namespace LaptimerCore::Test::Dummy

#endif //!__POSITIONS__H__