#include <gtk/gtk.h>
#include "files.h"
#include "window.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    int init = initialize();
    if (init != 0) {
	return 1;
    }
}
