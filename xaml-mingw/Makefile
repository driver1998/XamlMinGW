CXXFLAGS=-std=c++20 -march=core2
INCLUDES=-Icppwinrt -Iinclude
LIBS=-lole32 -loleaut32
LDFLAGS=-mwindows -static

all: xaml-mingw.exe

cppwinrt-headers: MainWindowView.winmd MainWindowViewModel.winmd
	cppwinrt -pch . -input references/Windows.winmd -output cppwinrt
	cppwinrt -pch . -input *.winmd -reference references/Windows.winmd -component cppwinrt/stub -output cppwinrt
	touch cppwinrt-headers

MainWindowView.winmd: MainWindowView.idl
	./gen_winmd.cmd $<

MainWindowView.o: MainWindowView.cpp cppwinrt-headers
	clang++ -c ${CXXFLAGS} ${INCLUDES} $< -o $@

MainWindowViewModel.winmd: MainWindowViewModel.idl
	./gen_winmd.cmd $<

MainWindowViewModel.o: MainWindowViewModel.cpp cppwinrt-headers
	clang++ -c ${CXXFLAGS} ${INCLUDES} $< -o $@

main.o: main.cpp cppwinrt-headers
	clang++ -c ${CXXFLAGS} ${INCLUDES} $< -o $@

module.g.o: cppwinrt-headers
	clang++ -c ${CXXFLAGS} ${INCLUDES} cppwinrt/module.g.cpp -o $@

app.res: app.rc app.manifest
	windres app.rc -o app.res

xaml-mingw.exe: main.o MainWindowView.o MainWindowViewModel.o module.g.o app.res
	clang++ $^ ${LIBS} ${LDFLAGS} -o $@

clean:
	rm -rf *.exe *.winmd *.o *.res cppwinrt cppwinrt-headers
