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
#include "window.h"

/* functions used by GTK/Glade */
void on_buttonfolder_clicked();
int on_buttoncontinue_clicked();

/* normal functions */
void initarguments(Arguments*, size_t);
void freearguments(Arguments*);
int getlevel(char*);

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


int
getlevel(char *level)
/* converts "||LEVEL[number]||" string to it's respecitve integer, otherwise returns NOTLEVEL(99 )to indicate that it's a file */
{
    int numberlevel;

    if (strncmp(level, "||LEVEL_", 8) == LEVEL) {
	numberlevel = level[8] - '0';
	return numberlevel;
    } else
	return NOTLEVEL;
}


int
on_buttoncontinue_clicked()
/* function to execute when button with the "ok"/"accept" icon is clicked */
/* A lot of debbuing in this function, please ignore it... I'm fixing it */
{
    const char      *path;
    Arguments        arg;
    /* int        currentlevel; */

    initarguments(&arg, 40);

    /* gets text from textbox of the first screen */
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

    /* for (int i = 0; i < us; i++) { */
    /* 	if ((islevel(arg.array[i])) == 0) */
    /* 	    free(arg.array[i]); */
    /* } */

    return 0;
}

void
on_buttonfolder_clicked()
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
initialize()
/* function to initialize the main window */
{
    char           *gladepath;

    gladepath = ""; /* path to xml builder file */
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
