#include <gtk/gtk.h>

#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <error.h>

#include "files.h"

/* functions used by GTK/Glade */
void on_buttonfolder_clicked(GtkButton*);
int on_buttoncontinue_clicked(GtkButton*);

/* normal functions */
void addrows();

typedef struct {
    GtkTreeIter mainiter;
    GtkTreeIter iterchild1;
    GtkTreeIter iterchild2;
    GtkTreeIter iterchild3;
    GtkTreeIter iterchild4;
    GtkTreeIter iterchild5;
    GtkTreeIter iterchild6;
    GtkTreeIter iterchild7;
    GtkTreeIter iterchild8;
    GtkTreeIter iterchild9;
} Dirlevels;

typedef struct {
    GtkWidget      *Win;
    GtkBuilder     *Bui;
    GtkWindow      *ParenWin;
} Window; /* structure that holds main window */

/* global variables to be able to access functions */
Window          window;
GtkWidget      *textbox;
GtkWidget      *notebook;
GtkEntryBuffer *entrybuffer;

void
initarguments(Arguments *a, size_t initialsize)
{
    a->array = malloc(initialsize * sizeof(char*));
    a->used = 0;
    a->size = initialsize;
}

void
freearguments(Arguments *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

int
getlevel(char *level)
{
    int numberlevel;

    if (strncmp(level, "||LEVEL_", 8) == 0) {
	numberlevel = level[8] - '0';
	return numberlevel;
    } else
	return 99;
}

int
on_buttoncontinue_clicked(GtkButton *b)
/* function to execute when button with the "ok"/"accept" icon is clicked */
{
    char      *path;
    Arguments  arg;
    int        currentlevel;

    initarguments(&arg, 10);

    path = gtk_entry_buffer_get_text(entrybuffer);
    if (path == NULL) {
	return 1;
    }
    g_print("path: %s\n", path);
    resolvepath(path, 0, &arg);
    gtk_notebook_next_page(GTK_NOTEBOOK(notebook));

    int us = arg.used;

    /* for (int i = 0; i < us; i++) { */
    /* 	if ((currentlevel = getlevel(arg.array[i])) == 1) */
    /* 	    printf("Level: %d, Folder: %s\n", currentlevel, arg.array[i-1]); */

    /* 	if ((currentlevel = getlevel(arg.array[i])) == 2) */
    /* 	    printf("Level: %d, Folder: %s\n", currentlevel, arg.array[i-1]); */

    /* 	if ((currentlevel = getlevel(arg.array[i])) == 3) */
    /* 	    printf("Level: %d, Folder: %s\n", currentlevel, arg.array[i-1]); */

    /* 	if ((currentlevel = getlevel(arg.array[i])) == 4) */
    /* 	    printf("Level: %d, Folder: %s\n", currentlevel, arg.array[i-1]); */

    /* 	if ((currentlevel = getlevel(arg.array[i])) == 5) */
    /* 	    printf("Level: %d, Folder: %s\n", currentlevel, arg.array[i-1]); */

    /* 	if ((currentlevel = getlevel(arg.array[i])) == 6) */
    /* 	    printf("Level: %d, Folder: %s\n", currentlevel, arg.array[i-1]); */

    /* 	if ((currentlevel = getlevel(arg.array[i])) == 7) */
    /* 	    printf("Level: %d, Folder: %s\n", currentlevel, arg.array[i-1]); */

    /* 	if ((currentlevel = getlevel(arg.array[i])) == 8) */
    /* 	    printf("Level: %d, Folder: %s\n", currentlevel, arg.array[i-1]); */

    /* 	if ((currentlevel = getlevel(arg.array[i])) == 9) */
    /* 	    printf("Level: %d, Folder: %s\n", currentlevel, arg.array[i-1]); */

    /* 	if (getlevel(arg.array[i]) == 99) */
    /* 	    printf("Level: %d, File: %s\n", currentlevel, arg.array[i]); */
    /* } */
    printf("us: %d\n", us);

    printf("===============================================\n");
    for (int i = 0; i < us; i++) {
	printf("MANOOO: %s\n", arg.array[i]);
    }
    printf("===============================================\n");

    freearguments(&arg);

    return 0;
}

void
on_buttonfolder_clicked(GtkButton *b)
/* function to execute when the button with the "folder" icon is clicked */
{
    GtkFileChooserNative *native;
    GtkFileChooserAction  action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER; /* action the file dialog executes */
    gint                  res;

    returndir();
    entrybuffer = gtk_entry_get_buffer(GTK_ENTRY(textbox));
    native = gtk_file_chooser_native_new("Open folder", window.ParenWin, action, "Select", "Cancel"); /* use native file dialog */
    res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));
    if (res == GTK_RESPONSE_ACCEPT) {
	char *foldername;
	GtkFileChooser *chooser = GTK_FILE_CHOOSER(native);
	foldername = gtk_file_chooser_get_filename(chooser);
	gtk_entry_buffer_set_text(entrybuffer, foldername, -1); /* fills text box with the path to the folder selected */
	g_print("foldername: %s\n", foldername);
	g_free(foldername);
    }
    g_object_unref(native);
}

int
initialize(int argc, char *argv[])
/* function to initialize the main window */
{
    char           *gladepath;

    gladepath = "./ui/window.glade"; /* path to xml builder file */
    gtk_init(&argc, &argv);
    window.Bui = gtk_builder_new_from_file(gladepath); /* builds xml file */
    window.Win = GTK_WIDGET(gtk_builder_get_object(window.Bui, "window"));
    window.ParenWin = GTK_WINDOW(window.Win); /* gets window itself */
    gtk_window_set_title(window.ParenWin, "FPS");
    g_signal_connect(window.Win, "destroy", G_CALLBACK(gtk_main_quit), NULL); /* makes application close it's resources after finishing windowk */
    gtk_builder_connect_signals(window.Bui, NULL);
    notebook = GTK_WIDGET(gtk_builder_get_object(window.Bui, "notebook"));
    textbox = GTK_WIDGET(gtk_builder_get_object(window.Bui, "textbox"));
    gtk_widget_show(window.Win); /* shows main window */
    gtk_main(); /* makes GTK look for events */

    return 0;
}
