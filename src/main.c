#include <gtk/gtk.h>
#include "window.h"

Window          window;
GtkWidget      *textbox;
GtkWidget      *notebook;
GtkEntryBuffer *entrybuffer;

int
main(int argc, char *argv[])
{
    char           *gladepath;

    gtk_init(&argc, &argv);
    gladepath = "/home/artur/Programming/c/github/file-parameter-selector/ui/window.glade"; /* path to xml builder file */
    window.Bui = gtk_builder_new_from_file(gladepath); /* builds xml file */
    window.Win = GTK_WIDGET(gtk_builder_get_object(window.Bui, "window"));
    window.ParenWin = GTK_WINDOW(window.Win); /* gets window itself */
    gtk_window_set_title(window.ParenWin, "FPS");
    g_signal_connect(window.Win, "destroy", G_CALLBACK(gtk_main_quit), NULL); /* makes application close it's resources after finishing window */
    gtk_builder_connect_signals(window.Bui, NULL);
    notebook = GTK_WIDGET(gtk_builder_get_object(window.Bui, "notebook"));
    textbox = GTK_WIDGET(gtk_builder_get_object(window.Bui, "textbox"));
    gtk_widget_show(window.Win); /* shows main window */
    gtk_main(); /* makes GTK look for events */

    return 0;
}
