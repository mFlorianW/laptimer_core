#include "AsyncResultDb.hpp"

namespace LaptimerCore::Storage
{

AsyncResultDb::~AsyncResultDb() = default;
AsyncResultDb::AsyncResultDb(AsyncResultDb &&other) noexcept = default;
AsyncResultDb &AsyncResultDb::operator=(AsyncResultDb &&other) noexcept = default;

void AsyncResultDb::setDbResult(System::Result result, const std::string &errMsg) noexcept
{
    System::AsyncResult::setResult(result, errMsg);
}

} // namespace LaptimerCore::Storage
