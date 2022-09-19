#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "files.h"

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

    resolvepath(path);

    gtk_notebook_next_page(GTK_NOTEBOOK(notebook));
    //free(path);
}

void
on_buttonfolder_clicked(GtkButton *b) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
    gint res;

    returndir();

    entrybuffer = gtk_entry_get_buffer(GTK_ENTRY(textbox));
    dialog = gtk_file_chooser_dialog_new("Open folder", window.ParenWin, action, "Cancel", GTK_RESPONSE_CANCEL, "Select", GTK_RESPONSE_ACCEPT, NULL);
    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
	char *foldername;
	GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
	foldername = gtk_file_chooser_get_filename(chooser);
	gtk_entry_buffer_set_text(entrybuffer, foldername, -1);
	printf("foldername: %s\n", foldername);
	g_free(foldername);
    }
    gtk_widget_destroy(dialog);
}

int
main(int argc, char *argv[])
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

