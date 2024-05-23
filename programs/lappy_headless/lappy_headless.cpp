// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <EventLoop.hpp>
#include <csignal>

using namespace LaptimerCore::System;

namespace
{
void signalHandler(int)
{
    auto el = EventLoop{};
    el.postEvent(&el, std::make_unique<Event>(Event::Type::QuitEvent));
}

} // namespace

int main(int argc, char** argv)
{
    EventLoop eventLoop;

    // clang-format off
    struct sigaction action{};
    // clant-format on
    action.sa_handler = signalHandler;
    sigaction(SIGINT, &action, nullptr);
    sigaction(SIGTERM, &action, nullptr);

    eventLoop.exec();
    return 0;
}
