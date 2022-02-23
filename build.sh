#!/bin/sh
x86_64-w64-mingw32-g++ *.cpp -Wl,-Bstatic -static -static-libgcc -static-libstdc++\
	$(./wxWidgets-3.1.5/wx-config --libs --cxxflags) \
	-I. -IwxWidgets-3.1.5/include \
	-LwxWidgets_3.1.4/lib -o xBeeGUI.exe "$@"
