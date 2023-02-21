CXX=c++
WINDRES=windres
CXXFLAGS=-std=c++20 -mcx16
INCLUDES=-Icppwinrt -Iinclude
LIBS=-lole32 -loleaut32
LDFLAGS=-mwindows -static

all: xaml-mingw.exe

cppwinrt-headers:
	cppwinrt -pch . -input references/Windows.winmd -output cppwinrt
	touch cppwinrt-headers

%.o: %.cpp %.h cppwinrt-headers
	${CXX} -c ${CXXFLAGS} ${INCLUDES} $< -o $@

main.o: main.cpp cppwinrt-headers
	${CXX} -c ${CXXFLAGS} ${INCLUDES} $< -o $@

app.res: app.rc app.manifest
	${WINDRES} app.rc -o app.res

xaml-mingw.exe: main.o MainWindowView.o MainWindowViewModel.o SimpleCommand.o CustomProperty.o app.res
	${CXX} $^ ${LIBS} ${LDFLAGS} -o $@

clean:
	rm -rf *.exe *.winmd *.o *.res cppwinrt cppwinrt-headers
