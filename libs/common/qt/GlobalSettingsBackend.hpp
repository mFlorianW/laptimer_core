// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include <QSettings>

namespace LaptimerCore::Common
{

class GlobalSettingsBackend
{
public:
    /**
     * Default destructor
     */
    ~GlobalSettingsBackend() = default;

    /**
     * Deleted copy constructor
     */
    GlobalSettingsBackend(GlobalSettingsBackend const&) = delete;

    /**
     * Deleted copy operator
     */
    GlobalSettingsBackend& operator=(GlobalSettingsBackend const&) = delete;

    /**
     * Deleted copy constructor
     */
    GlobalSettingsBackend(GlobalSettingsBackend&&) noexcept = delete;

    /**
     * Deleted move operator
     */
    GlobalSettingsBackend& operator=(GlobalSettingsBackend&&) noexcept = delete;

    /**
     * Stores a value under the given key.
     * @param key The key under which the value shall be stored to load it later.
     * @param value The value that shall be stored.
     * @return true Successful stored.
     *         false Failed to store.
     */
    [[nodiscard]] virtual bool storeValue(QString const& key, QVariant const& value) noexcept = 0;

protected:
    GlobalSettingsBackend() = default;
};

/**
 * QSettings based implementation of the @ref ISettingsBackend
 */
class QSettingsBackend : public GlobalSettingsBackend
{
public:
    /**
     * Creates an instance of the QSettings backend
     */
    QSettingsBackend();

    /**
     * Default empty destructor
     */
    ~QSettingsBackend() = default;

    /**
     * Deleted copy constructor
     */
    QSettingsBackend(QSettingsBackend const&) = delete;

    /**
     * Deleted copy operator
     */
    QSettingsBackend& operator=(QSettingsBackend const&) = delete;

    /**
     * Deleted copy constructor
     */
    QSettingsBackend(QSettingsBackend&&) noexcept = delete;

    /**
     * Deleted move operator
     */
    QSettingsBackend& operator=(QSettingsBackend&&) noexcept = delete;

    /**
     * @copydoc ISettingsBackend::storeValue
     */
    bool storeValue(QString const& key, QVariant const& value) noexcept override;

private:
    QSettings mSettings;
};

} // namespace LaptimerCore::Common
