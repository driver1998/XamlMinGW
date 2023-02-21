#include "CustomProperty.h"

namespace winrt::XamlMinGW::implementation
{
    CustomProperty::CustomProperty(CustomPropertyMetaData metadata)
    {
        m_metadata = metadata;
    }

    bool CustomProperty::CanRead() { return m_metadata.CanRead; }
    bool CustomProperty::CanWrite() { return m_metadata.CanRead; }
    hstring CustomProperty::Name() { return m_metadata.Name; }
    TypeName CustomProperty::Type() {return m_metadata.Type; }

    IInspectable CustomProperty::GetValue(IInspectable target)
    {
        if (!CanRead() || m_metadata.Getter == nullptr)
        {
            throw hresult_not_implemented();
        }

        return m_metadata.Getter(target);
    }

    IInspectable CustomProperty::GetIndexedValue(IInspectable target, IInspectable index)
    {
        throw hresult_not_implemented();
    }

    void CustomProperty::SetValue(IInspectable target, IInspectable value)
    {
        if (!CanWrite() || m_metadata.Setter == nullptr)
        {
            throw hresult_not_implemented();
        }

        m_metadata.Setter(target, value);
    }

    void CustomProperty::SetIndexedValue(IInspectable target, IInspectable value, IInspectable index) 
    {
        throw hresult_not_implemented();
    }
}
