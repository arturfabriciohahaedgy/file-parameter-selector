CC = cc
PKG-CONFIG= `pkg-config --cflags --libs gtk+-3.0`
CFLAGS = -Wall -Wextra -pipe -O2 -export-dynamic

FPS: src/window.c src/files.c
	${CC} src/window.c src/files.c -o FPS ${PKG-CONFIG} ${CFLAGS}
