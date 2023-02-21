#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Data.h>

namespace winrt::XamlMinGW::implementation
{
    struct MainWindowViewModel : winrt::implements<MainWindowViewModel, winrt::Windows::UI::Xaml::Data::ICustomPropertyProvider, winrt::Windows::UI::Xaml::Data::INotifyPropertyChanged>
    {
        MainWindowViewModel();

        hstring Message();
        void Message(hstring const& value);
        hstring UserName();
        void UserName(hstring const& value);
        winrt::Windows::UI::Xaml::Input::ICommand GreetingCommand();
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
        winrt::Windows::UI::Xaml::Data::ICustomProperty GetCustomProperty(hstring const& name);
        winrt::Windows::UI::Xaml::Data::ICustomProperty GetIndexedProperty(hstring const& name, winrt::Windows::UI::Xaml::Interop::TypeName const& type);
        hstring GetStringRepresentation();
        winrt::Windows::UI::Xaml::Interop::TypeName Type();

        private:
        hstring m_message;
        hstring m_userName;
        winrt::event<winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChangedEvent;
        winrt::Windows::UI::Xaml::Input::ICommand m_greetingCommand;
        static std::map<hstring, winrt::Windows::UI::Xaml::Data::ICustomProperty> m_propertyMap;
    };
}
