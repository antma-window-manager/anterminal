#include <vte/vte.h>
#include <gtk/gtk.h>

#include "config.h"

#define OPACITY_STEP 0.05
#define MIN_OPACITY 0.1
#define MAX_OPACITY 1.0

GtkWidget *window;

static gboolean
on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    VteTerminal *terminal = VTE_TERMINAL(user_data);

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
    } else if ((event->state & GDK_CONTROL_MASK) && (event->state & GDK_SHIFT_MASK) && event->keyval == GDK_KEY_C) {
        vte_terminal_copy_clipboard_format(terminal, VTE_FORMAT_TEXT);
        return TRUE;
    } else if ((event->state & GDK_CONTROL_MASK) && (event->state & GDK_SHIFT_MASK) && event->keyval == GDK_KEY_V) {
        vte_terminal_paste_clipboard(terminal);
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

static const GdkRGBA
sec_parse_color(const char *format)
{
    GdkRGBA color;
    if (!gdk_rgba_parse(&color, format)) {
        g_warning("Unable to parse color: %s", format);
        exit(EXIT_FAILURE);
    }

    return (const GdkRGBA) color;
}

static void
set_terminal_palette(VteTerminal *self)
{
    const GdkRGBA bg_color = sec_parse_color(CLR_BACKGROUND);
    const GdkRGBA fg_color = sec_parse_color(CLR_FOREGROUND);

    const GdkRGBA palette[] = {
        sec_parse_color(CLR_BLACK),
        sec_parse_color(CLR_RED),
        sec_parse_color(CLR_GREEN),
        sec_parse_color(CLR_YELLOW),
        sec_parse_color(CLR_BLUE),
        sec_parse_color(CLR_MAGENTA),
        sec_parse_color(CLR_CYAN),
        sec_parse_color(CLR_WHITE),
        sec_parse_color(CLR_LIGHT_BLACK),
        sec_parse_color(CLR_LIGHT_RED),
        sec_parse_color(CLR_LIGHT_GREEN),
        sec_parse_color(CLR_LIGHT_YELLOW),
        sec_parse_color(CLR_LIGHT_BLUE),
        sec_parse_color(CLR_LIGHT_MAGENTA),
        sec_parse_color(CLR_LIGHT_CYAN),
        sec_parse_color(CLR_LIGHT_WHITE)
    };

    vte_terminal_set_colors(self, &fg_color, &bg_color, palette, 16);
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
    gtk_window_set_title(GTK_WINDOW(window), "anterminal");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);

    GdkScreen *screen = gtk_widget_get_screen(window);
    GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
    if (visual != NULL)
    {
        gtk_widget_set_visual(window, visual);
    }

    gtk_widget_set_opacity(GTK_WIDGET(window), opacity);

    gchar *command[] = {"/bin/sh", "-c", "$SHELL", NULL};
    // gchar *command[] = {"/bin/sh", "-c", "PS1='anterminal > ' /bin/sh", NULL};

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
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), terminal);
    // set_terminal_text_color(VTE_TERMINAL(terminal), "#ffffff");
    set_terminal_palette(VTE_TERMINAL(terminal));
    vte_terminal_set_font(VTE_TERMINAL(terminal), pango_font_description_from_string(FONT));

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), terminal, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
