CC=g++
CXXFLAGS=-std=c++23 -Wall -Werror

all: corvus

corvus: gui.o webparser.o websocket.o urlparser.o browser.o corvus.o  
	${CC} ${CXXFLAGS} gui.o webparser.o websocket.o urlparser.o browser.o corvus.o -o corvus -lcrypto -lssl -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl src/lib/libimgui.a

corvus.o: src/corvus.cpp
	${CC} ${CXXFLAGS} -fmodules-ts -c src/corvus.cpp

browser.o: src/browser/browser.cppm
	${CC} ${CXXFLAGS} -fmodules-ts -c src/browser/browser.cppm

urlparser.o: src/url_parser/urlparser.cppm
	${CC} ${CXXFLAGS} -fmodules-ts -c src/url_parser/urlparser.cppm

websocket.o: src/websocket/websocket.cppm
	${CC} ${CXXFLAGS} -fmodules-ts -c src/websocket/websocket.cppm

webparser.o: src/webparser/webparser.cppm
	${CC} ${CXXFLAGS} -fmodules-ts -c src/webparser/webparser.cppm

gui.o: src/gui/gui.cppm
	${CC} ${CXXFLAGS} -fmodules-ts -c src/gui/gui.cppm


clean:
	rm *.o corvus