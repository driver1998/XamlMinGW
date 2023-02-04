#pragma once
#include "XamlMinGW/MainWindowView.g.h"

namespace winrt::XamlMinGW::implementation
{
    struct MainWindowView : MainWindowViewT<MainWindowView>
    {
        MainWindowView();
        void InitializeComponent();
    };
}
