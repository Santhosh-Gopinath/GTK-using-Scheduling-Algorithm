#ifndef __GTK_EXAMPLE_H__
#define __GTK_EXAMPLE_H__

#include <gtk/gtk.h>

// Function declarations
static void print_hello_callback(GtkWidget *widget, gpointer data);
static void activate(GtkApplication *app, gpointer user_data);
static void open_fcfs_page(GtkWidget *widget, gpointer data);
static void open_preemptive_sjf_page(GtkWidget *widget, gpointer data);
static void open_non_preemptive_sjf_page(GtkWidget *widget, gpointer data);
static void open_round_robin_page(GtkWidget *widget, gpointer data);
static void open_priority_page(GtkWidget *widget, gpointer data);

// Function definitions
static void print_hello_callback(GtkWidget *widget, gpointer data) {
    g_print("Process Scheduling Simulator\n");
}

static void open_new_page(GtkApplication *app, const gchar *title) {
    GtkWidget *new_window;
    GtkWidget *box;
    GtkWidget *label;

    new_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(new_window), title);
    gtk_window_set_default_size(GTK_WINDOW(new_window), 300, 200);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(new_window), box);

    label = gtk_label_new(title);
    gtk_widget_set_name(label, "label_title");
    gtk_box_append(GTK_BOX(box), label);

    gtk_window_present(GTK_WINDOW(new_window));
}

static void open_fcfs_page(GtkWidget *widget, gpointer data) {
    open_new_page(GTK_APPLICATION(data), "FCFS");
}

static void open_preemptive_sjf_page(GtkWidget *widget, gpointer data) {
    open_new_page(GTK_APPLICATION(data), "Preemptive SJF");
}

static void open_non_preemptive_sjf_page(GtkWidget *widget, gpointer data) {
    open_new_page(GTK_APPLICATION(data), "Non-Preemptive SJF");
}

static void open_round_robin_page(GtkWidget *widget, gpointer data) {
    open_new_page(GTK_APPLICATION(data), "Round Robin");
}

static void open_priority_page(GtkWidget *widget, gpointer data) {
    open_new_page(GTK_APPLICATION(data), "Priority");
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *hello_button;
    GtkWidget *fcfs_button;
    GtkWidget *preemptive_sjf_button;
    GtkWidget *non_preemptive_sjf_button;
    GtkWidget *round_robin_button;
    GtkWidget *priority_button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Process Scheduling Simulator");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), box);

    hello_button = gtk_button_new_with_label("Process Scheduling Simulator");
    gtk_widget_set_name(hello_button, "hello_button");
    g_signal_connect(hello_button, "clicked", G_CALLBACK(print_hello_callback), NULL);
    gtk_box_append(GTK_BOX(box), hello_button);

    fcfs_button = gtk_button_new_with_label("FCFS");
    gtk_widget_set_name(fcfs_button, "fcfs_button");
    g_signal_connect(fcfs_button, "clicked", G_CALLBACK(open_fcfs_page), app);
    gtk_box_append(GTK_BOX(box), fcfs_button);

    preemptive_sjf_button = gtk_button_new_with_label("Preemptive SJF");
    gtk_widget_set_name(preemptive_sjf_button, "preemptive_sjf_button");
    g_signal_connect(preemptive_sjf_button, "clicked", G_CALLBACK(open_preemptive_sjf_page), app);
    gtk_box_append(GTK_BOX(box), preemptive_sjf_button);

    non_preemptive_sjf_button = gtk_button_new_with_label("Non-Preemptive SJF");
    gtk_widget_set_name(non_preemptive_sjf_button, "non_preemptive_sjf_button");
    g_signal_connect(non_preemptive_sjf_button, "clicked", G_CALLBACK(open_non_preemptive_sjf_page), app);
    gtk_box_append(GTK_BOX(box), non_preemptive_sjf_button);

    round_robin_button = gtk_button_new_with_label("Round Robin");
    gtk_widget_set_name(round_robin_button, "round_robin_button");
    g_signal_connect(round_robin_button, "clicked", G_CALLBACK(open_round_robin_page), app);
    gtk_box_append(GTK_BOX(box), round_robin_button);

    priority_button = gtk_button_new_with_label("Priority");
    gtk_widget_set_name(priority_button, "priority_button");
    g_signal_connect(priority_button, "clicked", G_CALLBACK(open_priority_page), app);
    gtk_box_append(GTK_BOX(box), priority_button);

    gtk_window_present(GTK_WINDOW(window));

    // Load CSS for styling
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider,
        "#hello_button { background-color: #5f6caf; color: black; font-weight: bold; padding: 20px 40px; font-size: 16px; border-radius: 10px; }"
        "#fcfs_button { background-color: #ff6666; color: black; font-weight: bold; padding: 20px 40px; font-size: 16px; border-radius: 10px; }"
        "#preemptive_sjf_button { background-color: #ffcc66; color: black; font-weight: bold; padding: 20px 40px; font-size: 16px; border-radius: 10px; }"
        "#non_preemptive_sjf_button { background-color: #66ff66; color: black; font-weight: bold; padding: 20px 40px; font-size: 16px; border-radius: 10px; }"
        "#round_robin_button { background-color: #66ccff; color: black; font-weight: bold; padding: 20px 40px; font-size: 16px; border-radius: 10px; }"
        "#priority_button { background-color: #cc66ff; color: black; font-weight: bold; padding: 20px 40px; font-size: 16px; border-radius: 10px; }"
        "#label_title { font-size: 20px; font-weight: bold; color: #333333; }"
        "window { background-color: #f4e4c1; }"
    );

    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                               GTK_STYLE_PROVIDER(provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

#endif // __GTK_EXAMPLE_H__
