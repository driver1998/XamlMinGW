#include "ListItem.h"

namespace winrt::XamlMinGW::implementation {
    ListItem::ListItem(hstring const &name, hstring const &value) {
        Name.value = name;
        Value.value = value;
    }
} // namespace winrt::XamlMinGW::implementation