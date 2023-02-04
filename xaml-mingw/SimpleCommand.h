#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Input.h>

#include <functional>

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::UI::Xaml::Input;

struct SimpleCommand : winrt::implements<SimpleCommand, ICommand>
{
    SimpleCommand(std::function<void(IInspectable)> action)
    {
        m_action = action;
    }

    bool CanExecute(IInspectable parameter)
    {
        return true;
    }
    
    void Execute(IInspectable parameter)
    { 
        if (m_action != nullptr) m_action(parameter); 
    }

    winrt::event_token CanExecuteChanged(EventHandler<IInspectable> const& handler)
    {
        return m_eventToken.add(handler);
    }
    void CanExecuteChanged(winrt::event_token const& token) noexcept
    {
        m_eventToken.remove(token);
    }

    private:
    std::function<void(IInspectable)> m_action;
    winrt::event<EventHandler<IInspectable>> m_eventToken;
};