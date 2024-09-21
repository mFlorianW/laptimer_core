// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __NAVIGATEBLEMODEL__H__
#define __NAVIGATEBLEMODEL__H__

#include <cstdint>

class NavigatableModel
{
public:
    virtual ~NavigatableModel() = default;

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

#endif //!__NAVIGATEBLEMODEL__H__
