CC = cc
PKG-FLAGS= `pkg-config --cflags gtk+-3.0`
PKG-LIBS= `pkg-config --libs gtk+-3.0`
WINDOWSFLAGS = -Wall -Wextra -pipe -Wl,-export-all-symbols
CFLAGS = -Wall -Wextra -pipe -export-dynamic

FPS: src/main.c src/window.c src/files.c
	${CC} ${PKG-FLAGS} ${CFLAGS} src/main.c src/window.c src/files.c -o FPS ${PKG-LIBS}

debug: src/main.c src/window.c src/files.c
	${CC} -g ${PKG-FLAGS} ${CFLAGS} -g src/main.c src/window.c src/files.c -o fps-debug ${PKG-LIBS}

windows: src/main.c src/window.c src/files.c
	${CC} ${PKG-FLAGS} ${WINDOWSFLAGS} src/main.c src/window.c src/files.c -o FPS ${PKG-LIBS}

windebug: src/main.c src/window.c src/files.c
	${CC} -g ${PKG-FLAGS} ${WINDOWSFLAGS} -g src/main.c src/window.c src/files.c -o fps-debug ${PKG-LIBS}
