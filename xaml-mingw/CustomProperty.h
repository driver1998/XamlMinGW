#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.UI.Xaml.Interop.h>

#include <functional>

namespace winrt
{
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::UI::Xaml::Data;
    using namespace winrt::Windows::UI::Xaml::Interop;
}
namespace winrt::XamlMinGW::implementation
{
    struct CustomPropertyMetaData
    {
        bool CanRead;
        bool CanWrite;
        hstring Name;
        TypeName Type;

        std::function<IInspectable(IInspectable)> Getter;
        std::function<void(IInspectable, IInspectable)> Setter;
    };

    struct CustomProperty : winrt::implements<CustomProperty, ICustomProperty> {  

        CustomProperty(CustomPropertyMetaData metadata);
        
        bool CanRead();
        bool CanWrite();
        hstring Name();
        TypeName Type();
        
        IInspectable GetIndexedValue(IInspectable target, IInspectable index);
        IInspectable GetValue(IInspectable target);
        
        void SetIndexedValue(IInspectable target, IInspectable value, IInspectable index);
        void SetValue(IInspectable target, IInspectable value);
        
        private:
        CustomPropertyMetaData m_metadata;
    };

}
