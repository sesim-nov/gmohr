#include <iostream>
#include <iomanip>
#include <gtk/gtk.h>
#include <string>
#include <sstream>
#include "stressys.h"
using namespace std; 

struct passto{
	int variable_no;
	stressys *ss;
};

static gboolean delete_event(GtkWidget *widget, gpointer data){
g_print("Signal caught. Quitting!\n");
gtk_main_quit();
return FALSE;
}

void setstress(GtkWidget *widget, passto *data){
stringstream ss;
ss << gtk_entry_get_text(GTK_ENTRY(widget));
if (data->variable_no == 1) {
	ss >> data->ss->sx;
}
if (data->variable_no == 2) {
	ss >> data->ss->sy;
}
if (data->variable_no == 3) {
	ss >> data->ss->txy;
}
g_print("Changing values...\n");
}

void calc(GtkWidget *not_used, stressys *final){

GtkWidget *dialog;
GtkWidget *button;
GtkWidget *label;
GtkWidget *box;
stringstream stream1;
string out;

dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(dialog), "Results");
box = gtk_vbox_new(FALSE, 5);
gtk_container_add(GTK_CONTAINER(dialog),box);
final->mohr();

stream1 << "Maximum Normal Stress:\t"
	<< final->s1 << " psi"
	<< "\nMinimum Normal Stress:\t"
	<< final->s2 << " psi"
	<< "\nMaximum Shear Stress:\t"
	<< final->R << " psi"
	<< "\nAvg. Normal Stress:\t"
	<< final->C << "psi";
out = stream1.str();

g_print(out.c_str());
label = gtk_label_new(out.c_str());
gtk_box_pack_start(GTK_BOX(box),label,TRUE,FALSE,0);

button = gtk_button_new_with_label("Close Dialog");
gtk_box_pack_end(GTK_BOX(box), button,TRUE,FALSE,0);
g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), dialog);
gtk_widget_show_all(dialog);
out = "";
}


int main(int argc, char *argv[]){

GtkWidget *window;
GtkWidget *button;
GtkWidget *table;
GtkWidget *text;
GtkWidget *label;
stressys s1;
passto one = {1, &s1};
passto two = {2, &s1};
passto three = {3, &s1};
gtk_init(&argc, &argv);

window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
g_signal_connect(window, "delete_event", G_CALLBACK(delete_event), NULL);
gtk_window_set_title(GTK_WINDOW(window),"Mohr's Circle Calculator");
table = gtk_table_new(7,6,FALSE);

/* -------------------First Stress-------------------*/
label = gtk_label_new("First Normal Stress:"); 
gtk_table_attach_defaults(GTK_TABLE(table),label,0,3,1,2);

text = gtk_entry_new();
gtk_table_attach_defaults(GTK_TABLE(table),text,3,5,1,2);
g_signal_connect(text,"changed",G_CALLBACK(setstress),&one);

/* ------------------Second Stress------------------*/
label = gtk_label_new("Second Normal Stress:");
gtk_table_attach_defaults(GTK_TABLE(table),label,0,3,2,3);

text = gtk_entry_new();
gtk_table_attach_defaults(GTK_TABLE(table),text,3,5,2,3);
g_signal_connect(text,"changed",G_CALLBACK(setstress),&two);

/* ------------------Shear Stress------------------*/
label = gtk_label_new("Shear Stress:");
gtk_table_attach_defaults(GTK_TABLE(table),label,0,3,3,4);

text = gtk_entry_new();
gtk_table_attach_defaults(GTK_TABLE(table),text,3,5,3,4);
g_signal_connect(text,"changed",G_CALLBACK(setstress),&three);

/* -----------------Okay button-------------------*/
button = gtk_button_new_with_label("OK");
gtk_table_attach_defaults(GTK_TABLE(table),button,3,4,5,6);
g_signal_connect(button,"clicked",G_CALLBACK(calc),&s1);

/* -----------------Cancel button----------------- */
button = gtk_button_new_with_label("Cancel");
gtk_table_attach_defaults(GTK_TABLE(table),button,4,5,5,6);
g_signal_connect(button,"clicked",G_CALLBACK(delete_event),NULL);

gtk_container_add(GTK_CONTAINER(window),table);

gtk_widget_show_all(window);

gtk_main();


}
