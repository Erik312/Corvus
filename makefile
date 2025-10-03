CC=g++
CXXFLAGS=-std=c++23 -Wall -Werror

all: spartan

spartan: spartan_gui.o webparser.o websocket.o urlparser.o browser.o spartan.o  
	${CC} ${CXXFLAGS} spartan_gui.o webparser.o websocket.o urlparser.o browser.o spartan.o -o spartan -lcrypto -lssl -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl src/lib/libimgui.a

spartan.o: src/spartan.cpp
	${CC} ${CXXFLAGS} -fmodules-ts -c src/spartan.cpp

browser.o: src/browser/browser.cppm
	${CC} ${CXXFLAGS} -fmodules-ts -c src/browser/browser.cppm

urlparser.o: src/url_parser/urlparser.cppm
	${CC} ${CXXFLAGS} -fmodules-ts -c src/url_parser/urlparser.cppm

websocket.o: src/websocket/websocket.cppm
	${CC} ${CXXFLAGS} -fmodules-ts -c src/websocket/websocket.cppm

webparser.o: src/webparser/webparser.cppm
	${CC} ${CXXFLAGS} -fmodules-ts -c src/webparser/webparser.cppm

spartan_gui.o: src/gui/spartan_gui.cppm
	${CC} ${CXXFLAGS} -fmodules-ts -c src/gui/spartan_gui.cppm



clean:
	rm *.o spartan