// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "ISignalDispatcher.hpp"
#include <thread>

namespace LaptimerCore::System
{

class SignalDispatcher : public ISignalDispatcher
{
public:
    /**
     * Default constructor
     */
    SignalDispatcher();

    /**
     * Default empty constructor
     */
    ~SignalDispatcher() override;

    /**
     * Deleted copy constructor
     */
    SignalDispatcher(SignalDispatcher const& other) = delete;

    /**
     * Deleted copy assignment operator
     */
    SignalDispatcher& operator=(SignalDispatcher const& other) = delete;

    /**
     * Deleted move constructor
     */
    SignalDispatcher(SignalDispatcher&& ohter) = delete;

    /**
     * Deleted move assignemnt operator
     */
    SignalDispatcher& operator=(SignalDispatcher&& other) = delete;

    /**
     * @copydoc ISignalDispatcher::exec()
     */
    void exec() noexcept override;

    /**
     * @copydoc ISignalDispatcher::registerObject()
     */
    Result registerObject(IDispatcherObject* obj, std::thread::id const& id) noexcept override;

    /**
     * @copydoc ISignalDispatcher::unregisterObject()
     */
    Result unregisterObject(IDispatcherObject* obj, std::thread::id const& id) noexcept override;

private:
    std::thread::id mThreadId;
};

} // namespace LaptimerCore::System
