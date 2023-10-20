#include <windows.h>

#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/base.h>


#include "MainWindowView.h"
#include "windows.ui.xaml.hosting.desktopwindowxamlsource.h"


using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Hosting;
using namespace winrt::Windows::UI::Xaml::Markup;
using namespace winrt::Windows::UI::Xaml::Controls;

DesktopWindowXamlSource _xamlSource{nullptr};
WindowsXamlManager _windowsXamlManager{nullptr};

LRESULT onCreate(HWND hwnd, CREATESTRUCTW *cs) {
    _xamlSource = DesktopWindowXamlSource();
    auto xamlSourceNative = _xamlSource.as<IDesktopWindowXamlSourceNative>();
    xamlSourceNative->AttachToWindow(hwnd);

    auto view = winrt::make<winrt::XamlMinGW::implementation::MainWindowView>();
    _xamlSource.Content(view);

    _xamlSource.TakeFocusRequested([](DesktopWindowXamlSource sender,
                                      DesktopWindowXamlSourceTakeFocusRequestedEventArgs args) {
        sender.Content().as<Control>().Focus(FocusState::Programmatic);
    });

    HWND hwndXaml;
    xamlSourceNative->get_WindowHandle(&hwndXaml);
    SetFocus(hwndXaml);

    return 0;
}

LRESULT onResize(HWND hwnd, WORD type, WORD width, WORD height) {
    if (_xamlSource) {
        auto xamlSourceNative = _xamlSource.as<IDesktopWindowXamlSourceNative>();
        if (xamlSourceNative) {
            HWND hwndXaml;
            xamlSourceNative->get_WindowHandle(&hwndXaml);

            SetWindowPos(hwndXaml, nullptr, 0, 0, width, height, SWP_SHOWWINDOW);
        }
    }
    return 0;
}

LRESULT onDpiChanged(HWND hwnd, WORD dpi, RECT *rectNewWindow) {
    SetWindowPos(hwnd, NULL, rectNewWindow->left, rectNewWindow->top,
                 rectNewWindow->right - rectNewWindow->left,
                 rectNewWindow->bottom - rectNewWindow->top, SWP_NOZORDER | SWP_NOACTIVATE);
    return 0;
}

LRESULT CALLBACK mainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        return onCreate(hwnd, (CREATESTRUCTW *)lParam);
    case WM_SIZE:
        return onResize(hwnd, wParam, LOWORD(lParam), HIWORD(lParam));
    case WM_DPICHANGED:
        return onDpiChanged(hwnd, HIWORD(wParam), (RECT *)lParam);
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int main() {

    winrt::init_apartment(winrt::apartment_type::single_threaded);
    _windowsXamlManager = WindowsXamlManager::InitializeForCurrentThread();

    HINSTANCE hInstance = GetModuleHandle(0);
    WNDCLASSEXW wndClass = {.cbSize = sizeof(WNDCLASSEXW),
                            .style = 0,
                            .lpfnWndProc = mainWindowProc,
                            .cbClsExtra = 0,
                            .cbWndExtra = 0,
                            .hInstance = hInstance,
                            .hIcon = nullptr,
                            .hCursor = nullptr,
                            .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
                            .lpszMenuName = nullptr,
                            .lpszClassName = L"XamlWnd",
                            .hIconSm = nullptr};

    RegisterClassExW(&wndClass);

    HWND hwnd = CreateWindowExW(0, L"XamlWnd", L"XamlWnd", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr,
                                hInstance, nullptr);

    ShowWindow(hwnd, SW_NORMAL);

    MSG msg;
    BOOL ret;
    while ((ret = GetMessageW(&msg, nullptr, 0, 0)) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}