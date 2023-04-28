#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Data.h>

namespace winrt
{
    using namespace winrt::Windows::UI::Xaml::Data;
    using namespace winrt::Windows::UI::Xaml::Input;
    using namespace winrt::Windows::UI::Xaml::Interop;
}

namespace winrt::XamlMinGW::implementation
{
    struct ListItem : winrt::implements<ListItem, ICustomPropertyProvider, INotifyPropertyChanged>
    {
        ListItem(hstring const& name, hstring const& value);

        hstring Name();
        void Name(hstring const& value);
        hstring Value();
        void Value(hstring const& value);

        winrt::event_token PropertyChanged(PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

        ICustomProperty GetCustomProperty(hstring const& name);
        ICustomProperty GetIndexedProperty(hstring const& name, TypeName const& type);
        hstring GetStringRepresentation();
        TypeName Type();

        private:
        hstring m_name;
        hstring m_value;
        winrt::event<PropertyChangedEventHandler> m_propertyChangedEvent;
        
        static std::map<hstring, ICustomProperty> m_propertyMap;
    };
}
