#include <vte/vte.h>
#include <gtk/gtk.h>

#define OPACITY_STEP 0.05
#define MIN_OPACITY 0.1
#define MAX_OPACITY 1.0

GtkWidget *window;
double opacity = 0.8;

static gboolean
on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    if ((event->state & GDK_MOD1_MASK) && event->keyval == GDK_KEY_Up) {
        opacity += OPACITY_STEP;
        if (opacity > MAX_OPACITY) opacity = MAX_OPACITY;
        gtk_widget_set_opacity(window, opacity);
        return TRUE;
    } else if ((event->state & GDK_MOD1_MASK) && event->keyval == GDK_KEY_Down) {
        opacity -= OPACITY_STEP;
        if (opacity < MIN_OPACITY) opacity = MIN_OPACITY;
        gtk_widget_set_opacity(window, opacity);
        return TRUE;
    }

    return FALSE;
}

void set_terminal_text_color(VteTerminal *terminal, const char *color)
{
    GdkRGBA fg_color;
    if (gdk_rgba_parse(&fg_color, color)) {
        vte_terminal_set_colors(terminal,
        &fg_color,     // Foreground color
        NULL,          // Background color (use default)
        NULL,          // Palette
        0              // Number of palette colors
        );
    } else {
        g_warning("Failed to parse color: %s", color);
    }
}

static void
child_ready(VteTerminal *terminal, GPid pid, GError *error, gpointer user_data)
{
    if (!terminal) return;
    if (pid == -1) gtk_main_quit();
}

int main(int argc, char *argv[])
{
    GtkWidget *terminal, *vbox;

    gtk_init(&argc, &argv);
    terminal = vte_terminal_new();
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);

    GdkScreen *screen = gtk_widget_get_screen(window);
    GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
    if (visual != NULL)
    {
        gtk_widget_set_visual(window, visual);
    }

    gtk_widget_set_opacity(GTK_WIDGET(window), opacity);

    gchar *command[] = {"/bin/sh", "-c", "PS1='anterminal > ' /bin/sh", NULL};

    vte_terminal_spawn_async(VTE_TERMINAL(terminal),
    VTE_PTY_DEFAULT,
    NULL,
    command,
    NULL,
    0,
    NULL, NULL,
    NULL,
    -1,
    NULL,
    child_ready,
    NULL);

    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(terminal, "child-exited", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);
    set_terminal_text_color(VTE_TERMINAL(terminal), "#b722dd");

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), terminal, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
