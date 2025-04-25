#include <gtk/gtk.h> 
#include <curl/curl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#define MAX_EMAIL_LENGTH 1024 
#define MAX_CONTENT_LENGTH 2048 
typedef struct { 
    char* payload; 
    size_t size; 
} EmailData; 
const char* offensive_words[] = { 
    "spam" 
}; 
size_t payload_source(void* ptr, size_t size, size_t nmemb, void* userp) { 
    EmailData* email_data = (EmailData*)userp; 
    size_t data_size = size * nmemb; 
    if (email_data->size > 0) { 
        size_t copy_size = (data_size < email_data->size) ? data_size : 
email_data->size; 
        memcpy(ptr, email_data->payload, copy_size); 
        email_data->payload += copy_size; 
        email_data->size -= copy_size; 
        return copy_size; 
    } 
    return 0; 
} 
int check_spam(const char* content) { 
    int spam_score = 0; 
    int num_offensive_words = sizeof(offensive_words) / 
sizeof(offensive_words[0]); 
    char content_lower[MAX_CONTENT_LENGTH]; 
    int i; 
    strcpy(content_lower, content); 
    for (i = 0; content_lower[i]; i++) { 
        content_lower[i] = tolower(content_lower[i]);
 
    } 
    for (i = 0; i < num_offensive_words; i++) { 
        if (strstr(content_lower, offensive_words[i]) != NULL) { 
            spam_score++; 
        } 
    } 
    int caps_count = 0; 
    for (i = 0; content[i]; i++) { 
        if (isupper(content[i])) { 
            caps_count++; 
        } 
    } 
    if (caps_count > strlen(content) * 0.5) { 
        spam_score++; 
    } 
    return spam_score; 
} 
int send_secure_email(const char* smtp_server, const char* username, const 
char* password, 
                      const char* from, const char* to, const char* subject, 
const char* content) { 
    CURL* curl; 
    CURLcode res; 
    struct curl_slist* recipients = NULL; 
    EmailData email_data; 
    char email_payload[MAX_EMAIL_LENGTH]; 
    int spam_score = check_spam(content); 
    // Print spam detection result 
    if (spam_score >= 2) { 
        printf("Warning: Message appears to be spam (score: %d). Sending 
blocked.\n", spam_score); 
        return 1; 
    } else { 
        printf("Message content is clean (spam score: %d).\n", spam_score); 
    } 
    snprintf(email_payload, sizeof(email_payload), 
             "From: %s\r\n" 
             "To: %s\r\n" 
             "Subject: %s\r\n" 
             "\r\n" 
             "%s\r\n", 
             from, to, subject, content); 
    email_data.payload = email_payload; 
 
    email_data.size = strlen(email_payload); 
    curl = curl_easy_init(); 
    if (!curl) { 
        printf("Failed to initialize CURL\n"); 
        return 1; 
    } 
    char smtp_url[256]; 
    snprintf(smtp_url, sizeof(smtp_url), "smtps://%s", smtp_server); 
    curl_easy_setopt(curl, CURLOPT_URL, smtp_url); 
    curl_easy_setopt(curl, CURLOPT_USERNAME, username); 
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password); 
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L); 
    recipients = curl_slist_append(recipients, to); 
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from); 
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients); 
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source); 
    curl_easy_setopt(curl, CURLOPT_READDATA, &email_data); 
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L); 
    res = curl_easy_perform(curl); 
 
    if (res != CURLE_OK) { 
        printf("Failed to send email: %s\n", curl_easy_strerror(res)); 
        curl_slist_free_all(recipients); 
        curl_easy_cleanup(curl); 
        return 1; 
    } 
    printf("Email sent successfully!\n"); 
    curl_slist_free_all(recipients); 
    curl_easy_cleanup(curl); 
    return 0; 
} 
// GTK UI callback function 
void on_send_button_clicked(GtkWidget *widget, gpointer data) { 
    GtkWidget **entries = (GtkWidget **)data; 
    const char *smtp_server = "smtp.gmail.com:465";  // Update with your SMTP 
server 
    const char *username = "arunalisha2004@gmail.com";   // Update with your 
email username 
    const char *password = "raek nxsx luxi riyu";          // Update with 
your email password 
    const char *from = gtk_entry_get_text(GTK_ENTRY(entries[0])); 
    const char *to = gtk_entry_get_text(GTK_ENTRY(entries[1])); 
 
 
    const char *subject = gtk_entry_get_text(GTK_ENTRY(entries[2])); 
    const char *content = gtk_entry_get_text(GTK_ENTRY(entries[3])); 
    send_secure_email(smtp_server, username, password, from, to, subject, 
content); 
} 
int main(int argc, char *argv[]) { 
    gtk_init(&argc, &argv); 
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
    gtk_window_set_title(GTK_WINDOW(window), "Secure Email Sender"); 
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); 
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); 
 
    GtkWidget *grid = gtk_grid_new(); 
    gtk_container_add(GTK_CONTAINER(window), grid); 
    GtkWidget *from_label = gtk_label_new("From:"); 
    GtkWidget *to_label = gtk_label_new("To:"); 
    GtkWidget *subject_label = gtk_label_new("Subject:"); 
    GtkWidget *content_label = gtk_label_new("Content:"); 
    GtkWidget *from_entry = gtk_entry_new(); 
    GtkWidget *to_entry = gtk_entry_new(); 
    GtkWidget *subject_entry = gtk_entry_new();  
 
    GtkWidget *content_entry = gtk_entry_new(); 
    gtk_entry_set_max_length(GTK_ENTRY(content_entry), MAX_CONTENT_LENGTH); 
    GtkWidget *send_button = gtk_button_new_with_label("Send"); 
    GtkWidget *entries[] = {from_entry, to_entry, subject_entry, 
content_entry}; 
    g_signal_connect(send_button, "clicked", 
G_CALLBACK(on_send_button_clicked), entries); 
    gtk_grid_attach(GTK_GRID(grid), from_label, 0, 0, 1, 1); 
    gtk_grid_attach(GTK_GRID(grid), from_entry, 1, 0, 1, 1); 
    gtk_grid_attach(GTK_GRID(grid), to_label, 0, 1, 1, 1); 
    gtk_grid_attach(GTK_GRID(grid), to_entry, 1, 1, 1, 1); 
    gtk_grid_attach(GTK_GRID(grid), subject_label, 0, 2, 1, 1); 
    gtk_grid_attach(GTK_GRID(grid), subject_entry, 1, 2, 1, 1); 
    gtk_grid_attach(GTK_GRID(grid), content_label, 0, 3, 1, 1); 
    gtk_grid_attach(GTK_GRID(grid), content_entry, 1, 3, 1, 1); 
    gtk_grid_attach(GTK_GRID(grid), send_button, 1, 4, 1, 1); 
    gtk_widget_show_all(window); 
    gtk_main(); 
    return 0; 
} 
 
