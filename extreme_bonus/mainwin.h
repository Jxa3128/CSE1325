#ifndef MAINWIN_H
#define MAINWIN_H

#include <gtkmm.h>
#include "store.h"

class EntryDialog : public Gtk::MessageDialog {
  public:
    // This constructor is identical to Gtk::MessageDialog
    // https://developer.gnome.org/gtkmm/stable/classGtk_1_1MessageDialog.html
    EntryDialog(Gtk::Window& parent,
                const Glib::ustring& message,
                bool use_markup=false,
                Gtk::MessageType type=Gtk::MESSAGE_OTHER,
                Gtk::ButtonsType buttons=Gtk::BUTTONS_OK_CANCEL //CANCEL DOES NOT WORK,
                bool modal=false);

    // These methods are identical to those of the same name in Gtk::Entry
    // https://developer.gnome.org/gtkmm/stable/classGtk_1_1Entry.html
    void set_text (const Glib::ustring& text);
    Glib::ustring get_text () const;
  private:
    Gtk::Entry* entry;
};


class Mainwin : public Gtk::Window {
    public:
        Mainwin();
        Mainwin(Store& store);
        virtual ~Mainwin();

    protected:
        void on_new_store_click();
        void on_add_sweet_click();
        void on_list_sweets_click();
        //void on_place_order_click();
        //void on_list_orders_click();
        void on_about_click();
        void on_quit_click();

    private:
        Store *_store;
        Gtk::MenuItem *menuitem_add_sweet;
        Gtk::MenuItem *menuitem_list_sweets;
        Gtk::MenuItem *menuitem_place_orders;
        Gtk::MenuItem *menuitem_list_orders;
        Gtk::ToolButton *add_sweet_button;
        Gtk::ToolButton *list_sweets_button;
        //Gtk::ToolButton *place_order_button;
        //Gtk::ToolButton *list_orders_button;
        Gtk::Label *data;
        Gtk::Label *msg;
        void reset_sensitivity();
};
#endif
