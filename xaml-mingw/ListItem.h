#pragma once
#include <vector>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/base.h>


#include "Property.hpp"

namespace winrt {
    using namespace winrt::Windows::UI::Xaml::Data;
    using namespace winrt::Windows::UI::Xaml::Input;
    using namespace winrt::Windows::UI::Xaml::Interop;
} // namespace winrt

namespace winrt::XamlMinGW::implementation {
    struct ListItem : winrt::implements<ListItem, ICustomPropertyProvider, INotifyPropertyChanged>,
                      PropertyObject<ListItem> {
        ListItem(hstring const &name, hstring const &value);

        std::function<void(hstring const &name)> onPropertyChanged = [this](hstring const &name) {
            PropertyChanged.event(*this, PropertyChangedEventArgs{name});
        };

        Property<hstring> Name{L"Name", winrt::xaml_typename<hstring>(), onPropertyChanged};
        Property<hstring> Value{L"Value", winrt::xaml_typename<hstring>(), onPropertyChanged};

        std::vector<IProperty *> PropertyList = {&Name, &Value};
        Event<PropertyChangedEventHandler> PropertyChanged;
    };
} // namespace winrt::XamlMinGW::implementation
