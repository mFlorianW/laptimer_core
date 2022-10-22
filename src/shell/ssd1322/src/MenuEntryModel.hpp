#ifndef __MENUENTRYMODEL__H__
#define __MENUENTRYMODEL__H__

#include "CloseCommand.hpp"
#include "INavigationHandler.hpp"
#include "IOpenCloseHandler.hpp"
#include "MenuEntryView.hpp"
#include "NavigatableModel.hpp"
#include "NavigateDownCommand.hpp"
#include "NavigateUpCommand.hpp"
#include "OpenCommand.hpp"
#include <kdbindings/signal.h>

/**
 * The MenuEnrtyModel is a entry in the menu tree. The MenuEntryModel is navigatable up and down and can open a new
 * view, which then can be a new MenuEntryModel or a normal view.
 */
class MenuEntryModel : public NavigatableModel, public IOpenCloseHandler, public INavigationHandler
{
public:
    MenuEntryModel(MenuEntryView &menuEntryView);

    View &getView();

    void addSubMenuEntry(const std::string &entryMainText,
                         View *settingsView,
                         const std::string &entrySecondaryText = "");

    void open() override;
    void close() override;
    void navigateDown() override;
    void navigateUp() override;

    KDBindings::Signal<> viewChanged;

private:
    struct SettingsEntry
    {
        std::string entryMainText;
        std::string entrySecondaryText;
        View *settingsView;
    };

    // Menu views
    MenuEntryView &mEntryView;
    MenuEntryView mSubEntryView;
    View *mActiveView{nullptr};
    std::vector<SettingsEntry> mSubViews;

    // Commands
    OpenCommand mOpenCommand;
    CloseCommand mCloseCommand;
    NavigateUpCommand mNavigateUpCommand;
    NavigateDownCommand mNavigateDownCommand;
};

#endif //!__MENUENTRYMODEL__H__
