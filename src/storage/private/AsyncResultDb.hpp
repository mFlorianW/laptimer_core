#pragma once

#include "AsyncResult.hpp"

namespace LaptimerCore::Storage
{

class AsyncResultDb final : public System::AsyncResult
{
public:
    using System::AsyncResult::AsyncResult;

    /**
     * Default destructor
     */
    ~AsyncResultDb() override;

    /**
     * Deleted copy constructor
     */
    AsyncResultDb(const AsyncResultDb &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    AsyncResultDb &operator=(const AsyncResultDb &other) = delete;

    /**
     * Move constructor
     */
    AsyncResultDb(AsyncResultDb &&ohter) noexcept;

    /**
     * Move assignemnt operator
     */
    AsyncResultDb &operator=(AsyncResultDb &&other) noexcept;

    void setDbResult(System::Result result, const std::string &errMsg = "") noexcept;
};

} // namespace LaptimerCore::Storage
