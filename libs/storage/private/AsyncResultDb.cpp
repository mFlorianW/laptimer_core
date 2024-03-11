#include "AsyncResultDb.hpp"

namespace LaptimerCore::Storage
{

AsyncResultDb::~AsyncResultDb() = default;
AsyncResultDb::AsyncResultDb(AsyncResultDb&& other) noexcept = default;
AsyncResultDb& AsyncResultDb::operator=(AsyncResultDb&& other) noexcept = default;

void AsyncResultDb::setDbResult(System::Result result, std::string const& errMsg) noexcept
{
    System::AsyncResult::setResult(result, errMsg);
}

} // namespace LaptimerCore::Storage
