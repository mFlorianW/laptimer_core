// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

namespace LaptimerCore::System
{

/**
 * A DispatcherObject is used to together with the ISignalDispatcher. This is the uniform interface between these
 * classes. The ISignalDispatcher calls dispatch to trigger the signal dispatching of the class if needed.
 */
class IDispatcherObject
{
public:
    /**
     * Default destructor
     */
    virtual ~IDispatcherObject() = default;

    /**
     * Deleted copy constructor
     */
    IDispatcherObject(IDispatcherObject const& other) = delete;

    /**
     * Deleted copy assignment operator
     */
    IDispatcherObject& operator=(IDispatcherObject const& other) = delete;

    /**
     * Default move constructor
     */
    IDispatcherObject(IDispatcherObject&& ohter) = default;

    /**
     * Default move assignemnt operator
     */
    IDispatcherObject& operator=(IDispatcherObject&& other) = default;

    /**
     * This function is called by the @ref SignalDispatcherRegistry to trigger
     * checks if any Signal shall be emitted.
     */
    virtual void dispatch() = 0;

protected:
    /**
     * Default constructor
     */
    IDispatcherObject() = default;
};
} // namespace LaptimerCore::System
