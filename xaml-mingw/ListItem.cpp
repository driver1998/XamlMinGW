#include "ListItem.h"
#include "CustomProperty.h"

namespace winrt::XamlMinGW::implementation
{
    ListItem::ListItem(hstring const& name, hstring const& value)
    {
        m_name = name;
        m_value = value;
    }

    hstring ListItem::Name()
    {
        return m_name;
    }
    void ListItem::Name(hstring const& value)
    {
        m_name = value;
        m_propertyChangedEvent(*this, PropertyChangedEventArgs{L"Name"});
    }

    hstring ListItem::Value()
    {
        return m_value;
    }
    void ListItem::Value(hstring const& value)
    {
        m_value = value;
        m_propertyChangedEvent(*this, PropertyChangedEventArgs{L"Value"});
    }
    
    /* INotifyPropertyChanged*/
    winrt::event_token ListItem::PropertyChanged(PropertyChangedEventHandler const& handler)
    {
        return m_propertyChangedEvent.add(handler);
    }
    void ListItem::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChangedEvent.remove(token);
    }

    /* ICustomPropertyProvider */
    ICustomProperty ListItem::GetCustomProperty(hstring const& name)
    {
        if (m_propertyMap.contains(name))
        {
            return m_propertyMap[name];
        }
        else
        {
            return nullptr;
        }
    }
    ICustomProperty ListItem::GetIndexedProperty(hstring const& name, TypeName const& type)
    {
        throw hresult_not_implemented();
    }
    hstring ListItem::GetStringRepresentation()
    {
        return L"XamlMinGW.ListItem";
    }
    TypeName ListItem::Type()
    {
        return TypeName {
            .Name = L"XamlMinGW.ListItem",
            .Kind = TypeKind::Custom
        };
    }

    std::map<hstring, ICustomProperty> ListItem::m_propertyMap
    {
        {
            L"Name",
            winrt::make<CustomProperty>(
                CustomPropertyMetaData {
                    .CanRead = true,
                    .CanWrite = true,
                    .Name = L"Name",
                    .Type = TypeName {
                        .Name = L"String",
                        .Kind = TypeKind::Primitive
                    },
                    .Getter = [](IInspectable obj) -> IInspectable
                    { 
                        return winrt::box_value(obj.as<ListItem>()->Name());
                    },
                    .Setter = [](IInspectable obj, IInspectable value)
                    { 
                        obj.as<ListItem>()->Name(winrt::unbox_value<winrt::hstring>(value));
                    }
                }
            )
        },
        {
            L"Value",
            winrt::make<CustomProperty>(
                CustomPropertyMetaData {
                    .CanRead = true,
                    .CanWrite = true,
                    .Name = L"Value",
                    .Type = TypeName {
                        .Name = L"String",
                        .Kind = TypeKind::Primitive
                    },
                    .Getter = [](IInspectable obj) -> IInspectable
                    { 
                        return winrt::box_value(obj.as<ListItem>()->Value());
                    },
                    .Setter = [](IInspectable obj, IInspectable value)
                    { 
                        obj.as<ListItem>()->Value(winrt::unbox_value<winrt::hstring>(value));
                    }
                }
            )
        }
    };
}