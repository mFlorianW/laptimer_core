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
    AsyncResultDb(AsyncResultDb const& other) = delete;

    /**
     * Deleted copy assignment operator
     */
    AsyncResultDb& operator=(AsyncResultDb const& other) = delete;

    /**
     * Move constructor
     */
    AsyncResultDb(AsyncResultDb&& ohter) noexcept;

    /**
     * Move assignemnt operator
     */
    AsyncResultDb& operator=(AsyncResultDb&& other) noexcept;

    void setDbResult(System::Result result, std::string const& errMsg = "") noexcept;
};

} // namespace LaptimerCore::Storage
