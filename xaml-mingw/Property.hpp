#pragma once
#include <functional>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.UI.Xaml.Interop.h>

using namespace winrt::Windows::UI::Xaml::Data;
using namespace winrt::Windows::UI::Xaml::Input;
using namespace winrt::Windows::UI::Xaml::Interop;
using winrt::Windows::Foundation::IInspectable;

namespace winrt::XamlMinGW::implementation {
    template <typename T>
    struct Event {
        winrt::event_token operator()(T const &handler) { return event.add(handler); }
        void operator()(winrt::event_token const &token) noexcept { event.remove(token); }
        winrt::event<T> event;
    };

    struct PropertyInfo : winrt::implements<PropertyInfo, ICustomProperty> {
        PropertyInfo(hstring name, TypeName type, std::function<IInspectable(IInspectable)> getter,
                     std::function<void(IInspectable, IInspectable)> setter) {
            m_name = name;
            m_type = type;
            m_getter = getter;
            m_setter = setter;
        }

        bool CanRead() { return true; }
        bool CanWrite() { return true; }
        hstring Name() { return m_name; };
        TypeName Type() { return m_type; };

        IInspectable GetIndexedValue(IInspectable target, IInspectable index) {
            throw hresult_not_implemented();
        }
        IInspectable GetValue(IInspectable target) { return m_getter(target); }

        void SetIndexedValue(IInspectable target, IInspectable value, IInspectable index) {
            throw hresult_not_implemented();
        }
        void SetValue(IInspectable target, IInspectable value) { m_setter(target, value); }

      private:
        hstring m_name;
        TypeName m_type;
        std::function<IInspectable(IInspectable)> m_getter;
        std::function<void(IInspectable, IInspectable)> m_setter;
    };

    struct IProperty {
        virtual hstring Name() = 0;
        virtual TypeName Type() = 0;
        virtual IInspectable Getter() = 0;
        virtual void Setter(IInspectable const &value) = 0;
    };

    template <typename T>
    struct Property : IProperty {
        Property(hstring name, TypeName type,
                 std::function<void(hstring const &)> onPropertyChanged) {
            m_name = name;
            m_type = type;
            m_onPropertyChanged = onPropertyChanged;
        }

        void operator()(T const &value) {
            this->value = value;
            this->m_onPropertyChanged(m_name);
        }
        T operator()() { return this->value; }

        hstring Name() { return m_name; }
        TypeName Type() { return m_type; }
        IInspectable Getter() { return winrt::box_value(this->value); }
        void Setter(IInspectable const &value) { this->value = winrt::unbox_value<T>(value); }

        T value;

      private:
        hstring m_name;
        TypeName m_type;
        std::function<void(hstring const &)> m_onPropertyChanged;
    };

    template <typename T>
    struct PropertyObject {
        ICustomProperty GetCustomProperty(hstring const &name) {
            if (PropertyMap().contains(name)) {
                return m_propertyMap[name];
            } else {
                return nullptr;
            }
        }
        ICustomProperty GetIndexedProperty(hstring const &name, TypeName const &type) {
            throw hresult_not_implemented();
        }
        hstring GetStringRepresentation() { return L"PropertyObject"; }
        TypeName Type() { return winrt::xaml_typename<IInspectable>(); }

      private:
        std::map<hstring, ICustomProperty> const &PropertyMap() {
            if (m_propertyMap.empty()) {
                auto self = static_cast<T *>(this);
                std::vector<IProperty *> const &propertyList = self->PropertyList;

                for (auto item : propertyList) {
                    auto propertyInfo = winrt::make<PropertyInfo>(
                        item->Name(), item->Type(),
                        [self, item](IInspectable obj) {
                            if (obj == *self) {
                                return item->Getter();
                            } else {
                                throw hresult_invalid_argument();
                            }
                        },
                        [item, self](IInspectable obj, IInspectable value) {
                            if (obj == *self) {
                                item->Setter(value);
                            } else {
                                throw hresult_invalid_argument();
                            }
                        });
                    m_propertyMap.emplace(item->Name(), propertyInfo);
                }
            }
            return m_propertyMap;
        }

        std::map<hstring, ICustomProperty> m_propertyMap;
    };
} // namespace winrt::XamlMinGW::implementation