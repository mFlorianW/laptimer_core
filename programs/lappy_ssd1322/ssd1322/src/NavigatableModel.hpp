// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <cstdint>

class NavigatableModel
{
public:
    virtual ~NavigatableModel() = default;

    // Delete copy constructor
    NavigatableModel(NavigatableModel const&) = delete;

    // Delete copy assignment operator
    NavigatableModel& operator=(NavigatableModel const&) = delete;

    // Delete move constructor
    NavigatableModel(NavigatableModel&&) = delete;

    // Delete move assignment operator
    NavigatableModel& operator=(NavigatableModel&&) = delete;

protected:
    NavigatableModel(std::size_t size);

    std::size_t getSize() const noexcept;
    void setSize(std::size_t size);
    std::size_t getIndex() const;

    void incrementIndex();
    void decrementIndex();

private:
    std::size_t mIndex{0};
    std::size_t mSize{0};
};
