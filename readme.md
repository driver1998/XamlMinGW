# MinGW XAML Islands Demo

This is a demo of WinRT XAML Islands with MinGW LLVM toolchain, it works on LLVM 15 on MSYS2 currently.

# Why

To stress test the new C++/WinRT MinGW support mostly, also it is fun.

# Build

To build this, you'll need the following:

- Visual Studio 2022 with the following workloads:\
  Desktop Development with C++ \
  Universal Windows Platform development \
   \
  We only use the MIDL 3.0 compiler `midl.exe` to generate `winmd` files, so if you know how to get it more easily, you can do that instead, and change `gen_winmd.cmd` accordingly. \
  Or maybe someday we'll get winmd support in `widl` or other OSS IDL compiler, who knows.

- C++/WinRT `cppwinrt.exe` in `$PATH`
- A MinGW LLVM toolchain, GCC is untested

The best way to get a working toolchain is install the following in MSYS2:

```
pacman -S mingw-w64-clang-x86_64-toolchain mingw-w64-clang-x86_64-cppwinrt
```

With this, just build using the makefile provided.

# What works

- XAML layout (load in **runtime** only)
- Data binding with `ICustomPropertyProvider` (see `MainWindowViewModel.cpp` on how to implement this, it sucks but eh)
- `ICommand`
- Setting events from code-behind

# What doesn't

- Compiled XAML and `x:Bind`
- Automatically generated control references via `x:Name` (so you'll need to crawl through the logical tree to get to your controls)
- Anything else? Feel free to hack around