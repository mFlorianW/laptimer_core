#pragma once

namespace LaptimerCore::Workflow
{
/**
 * This interface contains the functionality to download the Sessions from a laptimer
 */
class ISessionDownloadWorkflow
{
public:
    virtual ~ISessionDownloadWorkflow() noexcept = default;
};
} // namespace LaptimerCore::Workflow
