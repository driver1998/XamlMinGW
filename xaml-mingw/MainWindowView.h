#pragma once
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/base.h>


namespace winrt {
    using namespace winrt::Windows::UI::Xaml::Controls;
}

namespace winrt::XamlMinGW::implementation {
    struct MainWindowView : UserControlT<MainWindowView> {
        MainWindowView() = default;
        void InitializeComponent();
    };
} // namespace winrt::XamlMinGW::implementation
