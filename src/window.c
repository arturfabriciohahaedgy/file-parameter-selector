#include <gtk/gtk.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "files.h"
#include "window.h"

void on_buttonfolder_clicked(GtkButton*);
void on_buttoncontinue_clicked(GtkButton*);

typedef struct {
    GtkWidget      *Win;
    GtkBuilder     *Bui;
    GtkWindow      *ParenWin;
} Window;

Window          window;
GtkWidget      *textbox;
GtkWidget      *notebook;
GtkEntryBuffer *entrybuffer;

void
on_buttoncontinue_clicked(GtkButton *b) {
    char *path;

    path = gtk_entry_buffer_get_text(entrybuffer);

    g_print("path: %s\n", path);

    resolvepath(path);

    gtk_notebook_next_page(GTK_NOTEBOOK(notebook));
}

void
on_buttonfolder_clicked(GtkButton *b) {
    GtkFileChooserNative *native;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
    gint res;

    returndir();

    entrybuffer = gtk_entry_get_buffer(GTK_ENTRY(textbox));
    native = gtk_file_chooser_native_new("Open folder", window.ParenWin, action, "Select", "Cancel");
    res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));
    if (res == GTK_RESPONSE_ACCEPT) {
	char *foldername;
	GtkFileChooser *chooser = GTK_FILE_CHOOSER(native);
	foldername = gtk_file_chooser_get_filename(chooser);
	gtk_entry_buffer_set_text(entrybuffer, foldername, -1);
	g_print("foldername: %s\n", foldername);
	g_free(foldername);
    }
    g_object_unref(native);
}

int
initialize(int argc, char *argv[])
{
    char           *gladepath;

    gladepath = "./ui/window.glade";

    gtk_init(&argc, &argv);

    window.Bui = gtk_builder_new_from_file(gladepath);
    window.Win = GTK_WIDGET(gtk_builder_get_object(window.Bui, "window"));
    window.ParenWin = GTK_WINDOW(window.Win);

    g_signal_connect(window.Win, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(window.Bui, NULL);
    
    notebook = GTK_WIDGET(gtk_builder_get_object(window.Bui, "notebook"));
    textbox = GTK_WIDGET(gtk_builder_get_object(window.Bui, "textbox"));

    gtk_widget_show(window.Win);

    gtk_main();

    return 0;
}

