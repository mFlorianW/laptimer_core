// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#define CATCH_CONFIG_MAIN
#include "SharedDataPointer.hpp"
#include <catch2/catch.hpp>
#include <cstdint>

using namespace LaptimerCore::Common;

namespace
{
class TestData : public SharedData
{
public:
    TestData() = default;
    TestData(bool* descrutorCalledFlag)
        : SharedData()
        , dtorCalledFlag(descrutorCalledFlag)
    {
    }

    ~TestData()
    {
        if (dtorCalledFlag != nullptr) {
            *dtorCalledFlag = true;
        }
    }

    bool* dtorCalledFlag{nullptr};
    std::uint8_t dummyInt;
};
} // namespace

TEST_CASE("SharedDataPointer shall free stored data on destruction when reference count is 0")
{
    auto dtorFlag = false;
    auto* testData = new TestData{&dtorFlag};
    {
        auto const pointer = SharedDataPointer{testData};
    }

    REQUIRE(dtorFlag == true);
}

TEST_CASE("SharedDataPointer shall read only access to the object with operator ->.")
{
    auto testData = new TestData{};
    auto const pointer = SharedDataPointer<TestData>{testData};

    auto const value = pointer->dummyInt;

    REQUIRE(testData->ref == 1);
}

TEST_CASE("SharedDataPointer shall return an immutable reference to the shared data object.")
{
    auto testData = new TestData{};
    auto const pointer = SharedDataPointer<TestData>{testData};

    auto const& immutableRef = *pointer;

    REQUIRE(testData->ref == 1);
    REQUIRE(&immutableRef == &(*testData));
}

TEST_CASE("SharedDataPointer shall return an immutable pointer to the shared data object.")
{
    auto testData = new TestData{};
    auto const pointer = SharedDataPointer<TestData>{testData};

    TestData const* immutablePtr = pointer;

    REQUIRE(testData->ref == 1);
    REQUIRE(immutablePtr == testData);
}

TEST_CASE("SharedDataPointer shall increment the reference counter in the shared object when copying.")
{
    auto testData = new TestData{};
    auto pointer = SharedDataPointer<TestData>{testData};

    auto pointer2 = SharedDataPointer<TestData>{pointer};

    REQUIRE(testData->ref == 2);
}

TEST_CASE("SharedDataPointer shall increment the reference counter with copy assignment.")
{
    auto testData = new TestData{};
    auto testData2 = new TestData{};
    auto pointer = SharedDataPointer<TestData>{testData};
    auto pointer2 = SharedDataPointer<TestData>{testData2};

    pointer2 = pointer;

    REQUIRE(pointer.getRefCount() == 2);
}

TEST_CASE("SharedDataPointer shall create a copy on the shared data when writing to it with ref count > 1.")
{
    auto testData = new TestData{};
    auto pointer = SharedDataPointer<TestData>{testData};
    auto pointer2 = SharedDataPointer<TestData>{testData};

    REQUIRE(pointer.getRefCount() == 2);
    REQUIRE(pointer2.getRefCount() == 2);

    pointer->dummyInt = 5;

    REQUIRE(pointer->dummyInt == 5);
    REQUIRE(pointer.getRefCount() == 1);
    REQUIRE(pointer2.getRefCount() == 1);
}

TEST_CASE(
    "SharedDataPointer shall create a copy on the shared data when converting to mutable reference with ref count > 1.")
{
    auto testData = new TestData{};
    auto pointer = SharedDataPointer<TestData>{testData};
    auto pointer2 = SharedDataPointer<TestData>{testData};

    auto& testDataRef = *pointer;

    REQUIRE(pointer.getRefCount() == 1);
    REQUIRE(pointer2.getRefCount() == 1);
    REQUIRE(testDataRef.ref == 1);
}

TEST_CASE(
    "SharedDataPointer shall create a copy on the shared data when converting to mutable pointer with ref count > 1.")
{
    auto testData = new TestData{};
    auto pointer = SharedDataPointer<TestData>{testData};
    auto pointer2 = SharedDataPointer<TestData>{testData};

    TestData* testDataPointer = pointer;

    REQUIRE(pointer.getRefCount() == 1);
    REQUIRE(pointer2.getRefCount() == 1);
    REQUIRE(testDataPointer->ref == 1);
}

TEST_CASE("SharedDataPointer shall be able to compare with a different SharedDataPointer.")
{
    auto testData = new TestData{};
    auto pointer = SharedDataPointer<TestData>{testData};
    auto pointer2 = SharedDataPointer<TestData>{testData};

    REQUIRE(pointer == pointer2);
}

TEST_CASE("SharedDataPointer shall be able to check of unequal a different SharedDataPointer.")
{
    auto testData = new TestData{};
    auto testData2 = new TestData{};
    auto pointer = SharedDataPointer<TestData>{testData};
    auto pointer2 = SharedDataPointer<TestData>{testData2};

    REQUIRE(pointer != pointer2);
}
