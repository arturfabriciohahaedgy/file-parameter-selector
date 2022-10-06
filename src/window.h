#include <gtk/gtk.h>

typedef struct {
    GtkWidget      *Win;
    GtkBuilder     *Bui;
    GtkWindow      *ParenWin;
} Window; /* structure that holds main window */

/* functions used by GTK/Glade */
void on_buttonfolder_clicked();
int on_buttoncontinue_clicked();

/* main.c globals */
extern Window          window;
extern GtkWidget      *textbox;
extern GtkWidget      *notebook;
extern GtkEntryBuffer *entrybuffer;
