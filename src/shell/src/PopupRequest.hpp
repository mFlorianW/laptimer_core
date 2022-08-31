#ifndef __POPUPREQUEST__H__
#define __POPUPREQUEST__H__

#include <kdbindings/signal.h>
#include <string>

enum class PopupReturnType
{
    Cancled,
    Confirmed
};

/**
 * A Request to display a popup.
 */
class PopupRequest
{
public:
    PopupRequest() = default;
    ~PopupRequest() = default;

    /**
     * Gives the main text for the popup dialog
     * @return const std::string& The main text for the popup.
     */
    const std::string &getMainText() const;

    /**
     * Sets the main text for the popup
     * @param mainText The main text of the popup.
     */
    void setMainText(const std::string &mainText);

    /**
     * Gives the secondary text of the popup.
     * @return const std::string& The secondary text for the popup.
     */
    const std::string &getSecondaryText() const;

    /**
     * Sets the secondary text of the popup.
     */
    void setSecondaryText(const std::string &secondaryText);

    /**
     * This signal is emitted when popup is confirmed or canceld.
     */
    KDBindings::Signal<PopupReturnType> confirmed;

private:
    std::string mMainText;
    std::string mSecondaryText;
};

#endif //!__POPUPREQUEST__H__