CC = cc
LIBS= `pkg-config --libs gtk+-3.0`
CFLAGS = -Wall -Wextra -pipe -export-dynamic `pkg-config --cflags gtk+-3.0`
WINDOWSFLAGS = -Wall -Wextra -pipe -Wl,-export-all-symbols `pkg-config --cflags gtk+-3.0`

FPS: src/main.c src/window.c src/fps.c
	${CC} ${CFLAGS} src/main.c src/window.c src/fps.c -o FPS ${LIBS}

debug: src/main.c src/window.c src/fps.c
	${CC} -g ${CFLAGS} -g src/main.c src/window.c src/fps.c -o fps-debug ${LIBS}

windows: src/main.c src/window.c src/fps.c
	${CC} ${WINDOWSFLAGS} src/main.c src/window.c src/fps.c -o FPS ${LIBS}

windebug: src/main.c src/window.c src/fps.c
	${CC} -g ${WINDOWSFLAGS} -g src/main.c src/window.c src/fps.c -o fps-debug ${LIBS}
