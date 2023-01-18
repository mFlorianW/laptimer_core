#pragma once

namespace LaptimerCore::System
{

/**
 * The result of operation which may fail.
 */
enum class Result
{
    Ok, //< The opration is finshed sucessful
    Error, //< The operation failed
    NotFinished, //< The operation is not finished
};

} // namespace LaptimerCore::System
