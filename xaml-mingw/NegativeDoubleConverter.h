#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Data.h>

namespace winrt
{
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::UI::Xaml::Data;
    using namespace winrt::Windows::UI::Xaml::Interop;
}

namespace winrt::XamlMinGW::implementation
{
    struct NegativeDoubleConverter : winrt::implements<NegativeDoubleConverter, IValueConverter>
    {
        NegativeDoubleConverter() = default;

        IInspectable Convert(IInspectable const& value, TypeName const& type, IInspectable const& parameter, hstring const& language);
        IInspectable ConvertBack(IInspectable const& value, TypeName const& type, IInspectable const& parameter, hstring const& language);
    };
}