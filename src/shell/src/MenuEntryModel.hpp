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

class MenuEntryModel : public NavigatableModel, public IOpenCloseHandler, public INavigationHandler
{
public:
    MenuEntryModel(MenuEntryView &entryView);

    View &getView();

    void addSubMenuEntry(MenuEntryView *entryView, View *settingsView);

    void open() override;
    void close() override;
    void navigateDown() override;
    void navigateUp() override;

    KDBindings::Signal<> viewChanged;

private:
    struct SettingsEntry
    {
        MenuEntryView *entryView;
        View *settingsView;
    };

    // Menu views
    MenuEntryView &mEntryView;
    View *mActiveView{nullptr};
    std::vector<SettingsEntry> mSubViews;

    // Commands
    OpenCommand mOpenCommand;
    CloseCommand mCloseCommand;
    NavigateUpCommand mNavigateUpCommand;
    NavigateDownCommand mNavigateDownCommand;
};

#endif //!__MENUENTRYMODEL__H__