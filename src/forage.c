#include <gtk/gtk.h>
#include "forage.h"

int main(int argc, char **argv) {
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.mzyzc.forage", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	
	return g_application_run(G_APPLICATION(app), argc, argv);
}

static void activate(GtkApplication *app, gpointer user_data) {
	const int row_count = 100;

	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *menu_bar;
	GtkWidget *panes;
	GtkWidget *scrolled_window;
	GtkWidget *list_box;
	GtkWidget *text_box;
	GtkWidget *button;
	GtkWidget *button_box;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Forage");
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	menu_bar = gtk_menu_bar_new();
	g_object_set(G_OBJECT(menu_bar), "hexpand", 1);
	g_object_set(G_OBJECT(menu_bar), "vexpand", 0);
	gtk_container_add(GTK_CONTAINER(menu_bar), gtk_menu_item_new_with_label("File"));
	gtk_container_add(GTK_CONTAINER(menu_bar), gtk_menu_item_new_with_label("View"));
	gtk_grid_attach(GTK_GRID(grid), menu_bar, 0, 0, 1, 1);

	panes = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	g_object_set(G_OBJECT(panes), "expand", 1);
	gtk_grid_attach(GTK_GRID(grid), panes, 0, 1, 1, 1);

	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	g_object_set(G_OBJECT(scrolled_window), "expand", 1);
	gtk_paned_add1(GTK_PANED(panes), scrolled_window);

	list_box = gtk_list_box_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window), list_box);

	for (int i = 0; i < row_count; i++) {
		GtkWidget *row = create_row("Placeholder entry");
		gtk_list_box_insert(GTK_LIST_BOX(list_box), row, -1);
	}

	text_box = gtk_text_view_new();
	gtk_paned_add2(GTK_PANED(panes), text_box);

	button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	g_object_set(G_OBJECT(button_box), "vexpand", 0);
	gtk_grid_attach(GTK_GRID(grid), button_box, 0, 3, 1, 1);

	button = gtk_button_new_with_label("Button");
	gtk_container_add(GTK_CONTAINER(button_box), button);

	gtk_widget_show_all(window);
}

static GtkWidget *create_row(gchar *text) {
	GtkWidget *row;
	GtkWidget *box;
	GtkWidget *label;

 	row = gtk_list_box_row_new();

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_container_add(GTK_CONTAINER(row), box);

	label = gtk_label_new(text);
	gtk_container_add(GTK_CONTAINER(box), label);

	return row;
}

