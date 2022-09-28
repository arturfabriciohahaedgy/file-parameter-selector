#include <gtk/gtk.h>
#include "files.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    int init = initialize();
    if (init != 0) {
	return 1;
    }
}
