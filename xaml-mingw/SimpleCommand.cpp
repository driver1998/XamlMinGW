#include "SimpleCommand.h"
#include <functional>

namespace winrt::XamlMinGW::implementation {
    SimpleCommand::SimpleCommand(std::function<void(IInspectable)> action) { m_action = action; }

    bool SimpleCommand::CanExecute(IInspectable parameter) { return true; }

    void SimpleCommand::Execute(IInspectable parameter) {
        if (m_action != nullptr)
            m_action(parameter);
    }

    winrt::event_token SimpleCommand::CanExecuteChanged(EventHandler<IInspectable> const &handler) {
        return m_eventToken.add(handler);
    }
    void SimpleCommand::CanExecuteChanged(winrt::event_token const &token) noexcept {
        m_eventToken.remove(token);
    }
} // namespace winrt::XamlMinGW::implementation
