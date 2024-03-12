// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef POPUPREQUEST_HPP
#define POPUPREQUEST_HPP

#include "PopupViewDefinition.hpp"
#include <chrono>
#include <kdbindings/signal.h>
#include <string>

/**
 * A Request to display a popup.
 */
class PopupRequest
{
public:
    /**
     * Contructs a PopupRequest instance
     **/
    PopupRequest() = default;

    /**
     * Default destructor
     */
    ~PopupRequest() = default;

    /**
     * Deleted Copy Constructor
     */
    PopupRequest(PopupRequest const& other) = delete;

    /**
     * Deleted Copy assignment operator
     */
    PopupRequest& operator=(PopupRequest const& other) = delete;

    /**
     * Default move constructor.
     */
    PopupRequest(PopupRequest&& other) = default;

    /**
     * Default move assignment operator
     */
    PopupRequest& operator=(PopupRequest&& other) = default;

    /**
     * Gives the main text for the popup dialog
     * @return const std::string& The main text for the popup.
     */
    std::string const& getMainText() const noexcept;

    /**
     * Sets the main text for the popup
     * @param mainText The main text of the popup.
     */
    void setMainText(std::string const& mainText) noexcept;

    /**
     * Gives the secondary text of the popup.
     * @return const std::string& The secondary text for the popup.
     */
    std::string const& getSecondaryText() const noexcept;

    /**
     * Sets the secondary text of the popup.
     */
    void setSecondaryText(std::string const& secondaryText) noexcept;

    /**
     * Gives the status about the auto closing popup. On default autoclosing is false.
     * @return True means auto close the popup.
     */
    bool isAutoClosing() const noexcept;

    /**
     * Sets the auto closing mechanismus. The default timeout is 10 seconds.
     * @param autoClosing True the popup will be closed automatically after the set timeout.
     */
    void setAutoClosing(bool autoClosing) noexcept;

    /**
     * Sets the timeout for auto closing the popup. The timeout takes only effect when the @PopupRequest::setAutoclosing
     * is set to true.
     * @param timeout The timeout before the diaglog is closed.
     */
    void setAutoClosingTimeout(std::chrono::seconds timeout) noexcept;

    /**
     * Gives the auto closing timeout.
     * @return The auto closing timout in seconds.
     */
    std::chrono::seconds const& getAutoClosingTimeout() const noexcept;

    /**
     * This signal is emitted when popup is confirmed or canceld.
     */
    KDBindings::Signal<PopupReturnType> confirmed;

    /**
     * Gives the type of the request popup.
     * @return The type of the popup.
     */
    Type getPopupType() const noexcept;

    /**
     * Sets the type of the requested popup.
     * @param newPopupType The new type of the requested popup.
     */
    void setPopupType(Type newPopupType) noexcept;

private:
    std::string mMainText;
    std::string mSecondaryText;
    bool mAutoClosing{false};
    std::chrono::seconds mAutoClosingTimeout{10};
    Type mPopupType{Type::NoConfirmation};
};

#endif //! POPUPREQUEST_HPP
