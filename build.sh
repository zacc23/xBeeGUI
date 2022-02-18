#!/bin/sh
# http://wiki.codeblocks.org/index.php?title=Cross_Compiling_wxWidgets_Applications_on_Linux#Running_on_Linux
#$(wx-config --libs --cppflags)
#-DwxUSE_WINSOCK2=1
#wxWidgets_3.1.4/include/msvc/wx
x86_64-w64-mingw32-g++ *.cpp -Wl,-Bstatic -static -static-libgcc -static-libstdc++\
	$(./wxWidgets-3.1.5/wx-config --libs --cxxflags) \
	-I. -IwxWidgets_3.1.4/include -IwxWidgets_3.1.4/lib/vc142_x64_dll/mswu \
	-LwxWidgets_3.1.4/lib -o xBeeGUI.exe "$@"
