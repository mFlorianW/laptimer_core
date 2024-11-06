// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef JSONDESERIALIZER_HPP
#define JSONDESERIALIZER_HPP

#include "SessionData.hpp"
#include <ArduinoJson.h>
#include <optional>
#include <string>

namespace Rapid::Common
{
class JsonDeserializer
{
public:
    static std::optional<SessionData> deserializeSessionData(std::string const& rawData);
};

} // namespace Rapid::Common

#endif // JSONDESERIALIZER_HPP
