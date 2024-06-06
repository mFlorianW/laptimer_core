// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "EventLoop.hpp"
#include <catch2/catch.hpp>
#include <chrono>
#include <sstream>

using namespace LaptimerCore::System;

namespace LaptimerCore::Testhelper
{

template <typename T>
class IsBetweenMatcher : public Catch::MatcherBase<T>
{
    T m_begin, m_end;

public:
    IsBetweenMatcher(T begin, T end)
        : m_begin(begin)
        , m_end(end)
    {
    }

    bool match(T const& in) const override
    {
        return in >= m_begin && in <= m_end;
    }

    std::string describe() const override
    {
        std::ostringstream ss;
        ss << "is between " << m_begin << " and " << m_end;
        return ss.str();
    }
};

template <typename T>
IsBetweenMatcher<T> IsBetween(T begin, T end)
{
    return {begin, end};
}

// clang-format off
// NOLINTNEXTLINE
#define REQUIRE_COMPARE_WITH_TIMEOUT(value, expected, timeout) \
{ \
    auto eventLoop = EventLoop{}; \
    auto testSteps = (timeout).count() / 10; \
    \
    if (testSteps == 0) { \
        testSteps = 10; \
    } \
    \
    auto thread = std::thread{}; \
    \
    for (std::chrono::milliseconds i(0); i < (timeout); i += std::chrono::milliseconds(testSteps)) { \
        thread = std::thread([&eventLoop] { \
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); \
            eventLoop.quit(); \
        }); \
        eventLoop.exec(); \
        thread.join(); \
        if ((value) == (expected)) { \
            break; \
        } \
    } \
    \
    REQUIRE((value) == (expected)); \
}

//clang-fomrat on

} // namespace LaptimerCore::Testhelper
