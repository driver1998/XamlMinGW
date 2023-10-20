#include "NegativeDoubleConverter.h"

namespace winrt::XamlMinGW::implementation {
    IInspectable NegativeDoubleConverter::Convert(IInspectable const &value, TypeName const &type,
                                                  IInspectable const &parameter,
                                                  hstring const &language) {
        double o = -1.0 * winrt::unbox_value<double>(value);
        return winrt::box_value(o);
    }

    IInspectable NegativeDoubleConverter::ConvertBack(IInspectable const &value,
                                                      TypeName const &type,
                                                      IInspectable const &parameter,
                                                      hstring const &language) {
        double o = -1.0 * winrt::unbox_value<double>(value);
        return winrt::box_value(o);
    }
} // namespace winrt::XamlMinGW::implementation
