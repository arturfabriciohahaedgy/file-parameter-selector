CC = cc
PKG-CONFIG= `pkg-config --cflags --libs gtk+-3.0`
WINDOWSFLAGS = -Wall -Wextra -pipe -O2 -Wl,-export-all-symbols
CFLAGS = -Wall -Wextra -pipe -O2 -export-dynamic

FPS: src/main.c src/window.c src/files.c
	${CC} src/main.c src/window.c src/files.c -o FPS ${PKG-CONFIG} ${CFLAGS}

windows: src/main.c src/window.c src/files.c
	${CC} src/main.c src/window.c src/files.c -o FPS ${PKG-CONFIG} ${WINDOWSFLAGS}

windebug: src/main.c src/window.c src/files.c
	${CC} -g src/main.c src/window.c src/files.c -o FPS ${PKG-CONFIG} ${WINDOWSFLAGS}
