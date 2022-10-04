/*
 * Frontend of the program. Everything related to display the GUI on screen is in here.
 */

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

#include "fps.h"
#include "window.h"

/* functions used by GTK/Glade */
void on_buttonfolder_clicked();
int on_buttoncontinue_clicked();

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
