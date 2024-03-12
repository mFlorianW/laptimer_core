// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef POPUPVIEWDEFINITION_HPP
#define POPUPVIEWDEFINITION_HPP

/**
 * The type of a popup.
 */
enum class Type
{
    NoConfirmation, //<! The popup doesn't need a confirmation. Can be auto closed.
    Confirmattion //<! Modal popup the user must confirm the popup for closing.
};

/**
 * The return type of the popup.
 */
enum class PopupReturnType
{
    Cancled, //<! The popup was closed with cancel.
    Confirmed //<! The popup was closed with ok.
};

#endif // POPUPVIEWDEFINITION_HPP
