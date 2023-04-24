#pragma once
#include "SessionData.hpp"
#include <kdbindings/signal.h>

namespace LaptimerCore::Workflow
{

enum class DownloadResult
{
    Ok,
    Error
};

/**
 * This interface contains the functionality to download the Sessions from a laptimer
 * The session can be downloaded in a index based manner. The first session index starts at 0 and ends at sessionCount
 * - 1.
 */
class ISessionDownload
{
public:
    virtual ~ISessionDownload() noexcept = default;

    /**
     * Deleted copy constructor
     */
    ISessionDownload(const ISessionDownload &) = delete;

    /**
     * Deleted copy operator
     */
    ISessionDownload &operator=(const ISessionDownload &) = delete;

    /**
     * Deleted move constructor
     */
    ISessionDownload(ISessionDownload &&) = delete;

    /**
     * Deleted move operator
     */
    ISessionDownload &operator=(ISessionDownload &&) = delete;

    /**
     * Gives the number of stored sessions of the laptimer. The return value is only valid after calling
     * fetchSessionCount and the signal sessionCountFetched was emitted.
     * @return The amount of session that are stored on the device.
     */
    virtual std::size_t getSessionCount() const noexcept = 0;

    /**
     * Fetches the session count of a laptimer device.
     * Shall emit the signal sessionCountFetched when finshed.
     */
    virtual void featchSessionCount() noexcept = 0;

    /**
     * Gives the session data for the passed index. The return is only valid when the session was previously downloaded
     * with downloaded and the signal sessionDownloadFinshed.
     * @param index The index of the session.
     * @return The session data for the passed index.
     */
    std::optional<Common::SessionData> getSession(std::size_t index);

    /**
     * Downloads a specific session of the device.
     */
    virtual void downloadSession(std::size_t index) noexcept = 0;

    /**
     * This signal is emitted when the fetchSessionCount operation finshed.
     * @param DownloadResult The result of the call.
     */
    KDBindings::Signal<DownloadResult> sessionCountFetched;

    /**
     * This signal is emitted when a session download is finished.
     * @param std::size_t The index of the session which is finished.
     */
    KDBindings::Signal<std::size_t, DownloadResult> sessionDownloadFinshed;

protected:
    ISessionDownload() noexcept = default;
};
} // namespace LaptimerCore::Workflow
