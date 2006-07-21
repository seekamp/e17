#include "ephoto.h"

void ok_album(Ewl_Widget *w, void *event, void *data);
void ok_slideshow(Ewl_Widget *w, void *event, void *data);
void cancel(Ewl_Widget *w, void *event, void *data);

void destroy_cb(Ewl_Widget *w, void *event, void *data)
{
 ewl_widget_destroy(w);
 ewl_main_quit();
 w = NULL;
 event = NULL;
 data = NULL;
 return;
}

void ok_album(Ewl_Widget *w, void *event, void *data)
{
 char *home;
 char *entry_text;
 char database[PATH_MAX];
 char command[PATH_MAX];
 sqlite3 *db;
 Ewl_Widget *win;
 Ewl_Widget *parent;
 Ewl_Widget *next;
 Ewl_Widget *entry;
 Ewl_Widget *text;

 entry = data;

 entry_text = ewl_text_text_get(EWL_TEXT(entry));
 home = getenv("HOME");
 snprintf(database, PATH_MAX, "%s/.ephoto/ephoto_database", home);

 ewl_container_child_iterate_begin(EWL_CONTAINER(m->albums));

 while ((next = ewl_container_child_next(EWL_CONTAINER(m->albums))) != NULL)
 {
  if (!strcmp(entry_text, ewl_icon_label_get(EWL_ICON(next)))) 
  {
   parent = entry->parent;
   text = ewl_container_child_get(EWL_CONTAINER(parent), 0);
   ewl_text_text_set(EWL_TEXT(text), "Whoops! This album exists!\n Please try again!");
   w = NULL;
   event = NULL;
   data = NULL;
   return;
  }
 }

 snprintf(command, PATH_MAX, "INSERT OR IGNORE INTO albums (name) VALUES ('%s');", entry_text);

 sqlite3_open(database, &db);
 sqlite3_exec(db, command, NULL, NULL, NULL);
 sqlite3_close(db);

 m->icon = ewl_icon_new();
 ewl_icon_label_set(EWL_ICON(m->icon), entry_text);
 ewl_object_alignment_set(EWL_OBJECT(m->icon), EWL_FLAG_ALIGN_CENTER);
 ewl_callback_append(m->icon, EWL_CALLBACK_CLICKED, album_clicked_cb, NULL);
 ewl_container_child_append(EWL_CONTAINER(m->albums), m->icon);
 ewl_widget_show(m->icon);
 
 parent = entry->parent;
 win = parent->parent;
 ewl_widget_destroy(win); 

 w = NULL;
 event = NULL;
 data = NULL;
 return;
}

void ok_slideshow(Ewl_Widget *w, void *event, void *data)
{
 char *home;
 char *entry_text;
 char database[PATH_MAX];
 char command[PATH_MAX];
 sqlite3 *db;
 Ewl_Widget *win;
 Ewl_Widget *parent;
 Ewl_Widget *next;
 Ewl_Widget *entry;
 Ewl_Widget *text;

 entry = data;

 entry_text = ewl_text_text_get(EWL_TEXT(entry));
 home = getenv("HOME");
 snprintf(database, PATH_MAX, "%s/.ephoto/ephoto_database", home);

 ewl_container_child_iterate_begin(EWL_CONTAINER(m->slideshows));

 while ((next = ewl_container_child_next(EWL_CONTAINER(m->slideshows))) != NULL)
 {
  if (!strcmp(entry_text, ewl_icon_label_get(EWL_ICON(next))))
  {
   parent = entry->parent;
   text = ewl_container_child_get(EWL_CONTAINER(parent), 0);
   ewl_text_text_set(EWL_TEXT(text), "Whoops! This slideshow exists!\n Please try again!");
   w = NULL;
   event = NULL;
   data = NULL;
   return;
  }
 }

 snprintf(command, PATH_MAX, "INSERT OR IGNORE INTO slideshows (name) VALUES ('%s');", entry_text);

 sqlite3_open(database, &db);
 sqlite3_exec(db, command, NULL, NULL, NULL);
 sqlite3_close(db);

 m->icon = ewl_icon_new();
 ewl_icon_label_set(EWL_ICON(m->icon), entry_text);
 ewl_object_alignment_set(EWL_OBJECT(m->icon), EWL_FLAG_ALIGN_CENTER);
 ewl_callback_append(m->icon, EWL_CALLBACK_CLICKED, slideshow_clicked_cb, NULL);
 ewl_container_child_append(EWL_CONTAINER(m->slideshows), m->icon);
 ewl_widget_show(m->icon);

 parent = entry->parent;
 win = parent->parent;
 ewl_widget_destroy(win);

 w = NULL;
 event = NULL;
 data = NULL;
 return;
}


void cancel(Ewl_Widget *w, void *event, void *data)
{
 ewl_widget_destroy(EWL_WIDGET(data));
 w = NULL;
 event = NULL;
 data = NULL;
 return;
}

void add_album_cb(Ewl_Widget *w, void *event, void *data)
{
 Ewl_Widget *win;
 Ewl_Widget *vbox;
 Ewl_Widget *text;
 Ewl_Widget *entry;
 Ewl_Widget *hbox;
 Ewl_Widget *button;

 win = ewl_window_new();
 ewl_window_title_set(EWL_WINDOW(win), "Create an album");
 ewl_window_name_set(EWL_WINDOW(win), "Create an album");
 ewl_object_size_request(EWL_OBJECT(win), 243, 73);
 ewl_callback_append(win, EWL_CALLBACK_DELETE_WINDOW, cancel, win);
 ewl_widget_show(win);

 vbox = ewl_vbox_new();
 ewl_object_fill_policy_set(EWL_OBJECT(vbox), EWL_FLAG_FILL_ALL);
 ewl_container_child_append(EWL_CONTAINER(win), vbox);
 ewl_widget_show(vbox);

 text = ewl_text_new();
 ewl_text_text_set(EWL_TEXT(text), "Enter the name of the album you wish to create");
 ewl_container_child_append(EWL_CONTAINER(vbox), text);
 ewl_widget_show(text);

 entry = ewl_entry_new();
 ewl_container_child_append(EWL_CONTAINER(vbox), entry);
 ewl_widget_show(entry);

 hbox = ewl_hbox_new();
 ewl_object_fill_policy_set(EWL_OBJECT(hbox), EWL_FLAG_FILL_HFILL);
 ewl_container_child_append(EWL_CONTAINER(vbox), hbox);
 ewl_widget_show(hbox);

 button = ewl_button_new();
 ewl_button_label_set(EWL_BUTTON(button), "Ok");
 ewl_container_child_append(EWL_CONTAINER(hbox), button);
 ewl_callback_append(button, EWL_CALLBACK_CLICKED, ok_album, entry);
 ewl_widget_show(button);

 button = ewl_button_new();
 ewl_button_label_set(EWL_BUTTON(button), "Cancel");
 ewl_container_child_append(EWL_CONTAINER(hbox), button);
 ewl_callback_append(button, EWL_CALLBACK_CLICKED, cancel, win);
 ewl_widget_show(button);

 w = NULL;
 event = NULL;
 data = NULL;
 return;
}

void add_slideshow_cb(Ewl_Widget *w, void *event, void *data)
{
 Ewl_Widget *win;
 Ewl_Widget *vbox;
 Ewl_Widget *text;
 Ewl_Widget *entry;
 Ewl_Widget *hbox;
 Ewl_Widget *button;

 win = ewl_window_new();
 ewl_window_title_set(EWL_WINDOW(win), "Create a slideshow");
 ewl_window_name_set(EWL_WINDOW(win), "Create an slideshow");
 ewl_object_size_request(EWL_OBJECT(win), 243, 73);
 ewl_callback_append(win, EWL_CALLBACK_DELETE_WINDOW, cancel, win);
 ewl_widget_show(win);

 vbox = ewl_vbox_new();
 ewl_object_fill_policy_set(EWL_OBJECT(vbox), EWL_FLAG_FILL_ALL);
 ewl_container_child_append(EWL_CONTAINER(win), vbox);
 ewl_widget_show(vbox);

 text = ewl_text_new();
 ewl_text_text_set(EWL_TEXT(text), "Enter the name of the slideshow you wish to create");
 ewl_container_child_append(EWL_CONTAINER(vbox), text);
 ewl_widget_show(text);

 entry = ewl_entry_new();
 ewl_container_child_append(EWL_CONTAINER(vbox), entry);
 ewl_widget_show(entry);

 hbox = ewl_hbox_new();
 ewl_object_fill_policy_set(EWL_OBJECT(hbox), EWL_FLAG_FILL_HFILL);
 ewl_container_child_append(EWL_CONTAINER(vbox), hbox);
 ewl_widget_show(hbox);

 button = ewl_button_new();
 ewl_button_label_set(EWL_BUTTON(button), "Ok");
 ewl_container_child_append(EWL_CONTAINER(hbox), button);
 ewl_callback_append(button, EWL_CALLBACK_CLICKED, ok_slideshow, entry);
 ewl_widget_show(button);

 button = ewl_button_new();
 ewl_button_label_set(EWL_BUTTON(button), "Cancel");
 ewl_container_child_append(EWL_CONTAINER(hbox), button);
 ewl_callback_append(button, EWL_CALLBACK_CLICKED, cancel, win);
 ewl_widget_show(button);

 w = NULL;
 event = NULL;
 data = NULL;
 return;
}

void album_clicked_cb(Ewl_Widget *w, void *event, void *data)
{
 w = NULL;
 event = NULL;
 data = NULL;
 return;
}

void slideshow_clicked_cb(Ewl_Widget *w, void *event, void *data)
{
 w = NULL;
 event = NULL;
 data = NULL;
 return;
}
