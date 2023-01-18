#define CATCH_CONFIG_MAIN
#include "AsyncResult.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::System;

namespace
{
class TestAsyncResult : public AsyncResult
{
public:
    using AsyncResult::AsyncResult;

    void setResult(Result result, const std::string &errorMessage = std::string{})
    {
        AsyncResult::setResult(result, errorMessage);
    }
};
} // namespace

SCENARIO("The AsyncResult shall emit done signal when operation is finshed")
{
    GIVEN("A AsyncResult")
    {
        auto doneSignalEmitted = false;
        auto aResult = TestAsyncResult();
        auto *receivedResultPointer = static_cast<AsyncResult *>(nullptr);
        aResult.done.connect([&doneSignalEmitted, &receivedResultPointer](AsyncResult *asyncResult) {
            receivedResultPointer = asyncResult;
            doneSignalEmitted = true;
        });

        WHEN("The result is set in the AsyncResult")
        {
            aResult.setResult(Result::Ok);
            THEN("The signal shall be emitted.")
            {
                REQUIRE(doneSignalEmitted == true);
            }

            THEN("The signal parameter shall be the same as the origin result")
            {
                REQUIRE(receivedResultPointer == &aResult);
            }
        }
    }
}

SCENARIO("The AsyncResult shall set the result when operation is finshed")
{
    GIVEN("A AsyncResult")
    {
        auto aResult = TestAsyncResult{};

        WHEN("The result is set in the AsyncResult")
        {
            aResult.setResult(Result::Ok);
            THEN("The correct result type shall be returned")
            {
                REQUIRE(aResult.getResult() == Result::Ok);
            }
        }

        WHEN("No result is set in the AsyncResult")
        {
            THEN("The default return type shall be returned")
            {
                REQUIRE(aResult.getResult() == Result::NotFinished);
            }
        }
    }
}

SCENARIO("The AsyncResult shall return the error message when set")
{
    GIVEN("A AsyncResult")
    {
        auto aResult = TestAsyncResult{};
        auto errMsg = std::string{"This is a errr message."};

        WHEN("The result with a error message is set in the AsyncResult")
        {
            aResult.setResult(Result::Ok, errMsg);
            THEN("The correct result type shall be returned")
            {
                REQUIRE(aResult.getErrorMessage() == errMsg);
            }
        }
    }
}
