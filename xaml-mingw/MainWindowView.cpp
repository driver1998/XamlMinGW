

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>

#include "MainWindowView.h"
#include "MainWindowViewModel.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;

namespace winrt::XamlMinGW::implementation
{
    void MainWindowView::InitializeComponent()
    {
        Uri uri(L"ms-appx:///MainWindowView.xaml");
        Application::LoadComponent(*this, uri);

        auto viewModel = winrt::make<MainWindowViewModel>();
        auto viewModelImpl = winrt::get_self<MainWindowViewModel>(viewModel);
        viewModelImpl->UserName(L"MinGW");
        DataContext(viewModel);

        auto btn2 = this->FindName(L"btn2").as<Button>();
        if (btn2)
        {
            btn2.Click([](IInspectable const& sender, RoutedEventArgs const& args) -> winrt::fire_and_forget {
                ContentDialog dialog;
                dialog.Title(winrt::box_value(L"About"));
                dialog.Content(winrt::box_value(L"MinGW XAML Islands Demo"));
                dialog.CloseButtonText(L"OK");

                auto btn = sender.try_as<Button>();
                dialog.XamlRoot(btn.XamlRoot());

                co_await dialog.ShowAsync();
            });
        }
    }
}
