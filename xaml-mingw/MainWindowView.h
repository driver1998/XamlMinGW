#pragma once
#include <winrt/base.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>

namespace winrt::XamlMinGW::implementation
{
    struct MainWindowView : winrt::Windows::UI::Xaml::Controls::UserControlT<MainWindowView>
    {
        MainWindowView();
        void InitializeComponent();
    };
}
