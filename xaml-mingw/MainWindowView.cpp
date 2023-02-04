

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.h>

#include "MainWindowView.h"
#include "MainWindowViewModel.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::UI::Xaml;

namespace winrt::XamlMinGW::implementation
{
    MainWindowView::MainWindowView()
    {
        InitializeComponent();
    }

    void MainWindowView::InitializeComponent()
    {
        Uri uri(L"ms-appx:///MainWindowView.xaml");
        Application::LoadComponent(*this, uri);

        auto viewModel = winrt::make<winrt::XamlMinGW::implementation::MainWindowViewModel>();
        viewModel.UserName(L"MinGW");
        DataContext(viewModel);
    }
}
