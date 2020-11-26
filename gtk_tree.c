#include <gtk/gtk.h>

void print_button_msg() 
{
  g_print("Button clicked\n");
}

GdkPixbuf *create_pixbuf(const gchar * filename)
{
  GdkPixbuf *pixbuf;
  GError *error = NULL;
  pixbuf = gdk_pixbuf_new_from_file(filename, &error);

  if (!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
  }

  return pixbuf;
}

void set_params(GtkWidget  *window)
{
  gtk_window_set_title(GTK_WINDOW(window), "AVL Tree");
  gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(window), 15);
}

void set_icon(GtkWidget *window)
{
  GdkPixbuf *icon = create_pixbuf("assets/tree.png");
  gtk_window_set_icon(GTK_WINDOW(window), icon);
  g_object_unref(icon);
}

GtkWidget *create_button()
{
  GtkWidget *button = gtk_button_new_with_mnemonic("_Button");
  g_signal_connect(button, "clicked", G_CALLBACK(print_button_msg), NULL);
  GtkWidget *halign = gtk_alignment_new(0, 0, 0, 0);
  gtk_container_add(GTK_CONTAINER(halign), button);
  return halign;
}

void run_main_window(GtkWidget *window)
{
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show_all(window);
  gtk_main();
}

int main(int argc, char **argv) 
{
    
  GtkWidget *window;

  gtk_init(&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  set_params(window);
  set_icon(window);
  
  gtk_container_add(GTK_CONTAINER(window), create_button());

  run_main_window(window);

  return 0;
}
