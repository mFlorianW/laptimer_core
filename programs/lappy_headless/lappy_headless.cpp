// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <ConstantVelocityPositionDateTimeProvider.hpp>
#include <EventLoop.hpp>
#include <PositionData.hpp>
#include <array>
#include <csignal>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace LaptimerCore::System;
using namespace LaptimerCore::Positioning;

namespace
{
void signalHandler(int)
{
    auto el = EventLoop{};
    el.postEvent(&el, std::make_unique<Event>(Event::Type::QuitEvent));
}

std::vector<LaptimerCore::Common::PositionData> loadCsvPositions(std::string const filePath)
{
    auto positions = std::vector<LaptimerCore::Common::PositionData>{};
    auto file = std::fstream(filePath);
    auto line = std::string{};

    while (std::getline(file, line)) {
        std::istringstream input(line);
        std::array<std::string, 2> splittedLine;
        for (auto& i : splittedLine) {
            getline(input, i, ',');
        }

        auto longitude = std::stof(splittedLine[0]);
        auto latitude = std::stof(splittedLine[1]);

        positions.emplace_back(latitude, longitude);
    }

    return positions;
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

    // Load GPS position file
    auto positions = loadCsvPositions("/home/florian/Coding/laptimer_core/laps/Oschersleben.csv");

    auto positionProvider = ConstantVelocityPositionDateTimeProvider{positions};


    eventLoop.exec();
    return 0;
}
