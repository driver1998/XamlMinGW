#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.UI.Xaml.Interop.h>

#include <functional>

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::UI::Xaml::Data;
using namespace winrt::Windows::UI::Xaml::Interop;

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

    CustomProperty(CustomPropertyMetaData metadata)
    {
        m_metadata = metadata;
    }

    bool CanRead() { return m_metadata.CanRead; }
    bool CanWrite() { return m_metadata.CanRead; }
    hstring Name() { return m_metadata.Name; }
    TypeName Type() {return m_metadata.Type; }
    
    IInspectable GetIndexedValue(IInspectable target, IInspectable index)
    {
        throw hresult_not_implemented();
    }
    IInspectable GetValue(IInspectable target)
    {
        if (!CanRead() || m_metadata.Getter == nullptr)
        {
            throw hresult_not_implemented();
        }

        return m_metadata.Getter(target);
    }
    void SetIndexedValue(IInspectable target, IInspectable value, IInspectable index) { throw hresult_not_implemented(); }
    void SetValue(IInspectable target, IInspectable value)
    {
        if (!CanWrite() || m_metadata.Setter == nullptr)
        {
            throw hresult_not_implemented();
        }

        m_metadata.Setter(target, value);
    }

    private:
    CustomPropertyMetaData m_metadata;
};
