#include "mainwin.h"

#include <iostream>
Mainwin::Mainwin() : Mainwin{*(new Store)} { }
Mainwin::Mainwin(Store& store) : _store{&store} {

    // /////////////////
    // G U I   S E T U P
    // /////////////////
    set_default_size(600, 600);
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);
/////////////////////////////////////////////////////////////////////////////////////////
    // ///////
    // M E N U
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

/////////////////////////////////////////////////////////////////////////////////////////

    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem("_New Store", true));
    menuitem_new->signal_activate().connect([this] {this->on_new_store_click();});
    filemenu->append(*menuitem_new);

    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
    filemenu->append(*menuitem_quit);

///////////////////////////////////////////////////////////////////////////////////////////////

    Gtk::MenuItem *menuitem_sweets = Gtk::manage(new Gtk::MenuItem("_Sweets", true));
    menubar->append(*menuitem_sweets);
    Gtk::Menu *sweetsmenu = Gtk::manage(new Gtk::Menu());
    menuitem_sweets->set_submenu(*sweetsmenu);

    menuitem_add_sweet = Gtk::manage(new Gtk::MenuItem("_Add Sweets", true));
    menuitem_add_sweet->signal_activate().connect([this] {this->on_add_sweet_click();});
    sweetsmenu->append(*menuitem_add_sweet);


    menuitem_list_sweets = Gtk::manage(new Gtk::MenuItem("_List Sweets", true));
    menuitem_list_sweets->signal_activate().connect([this] {this->on_list_sweets_click();});
    sweetsmenu->append(*menuitem_list_sweets);
    menuitem_list_sweets->set_sensitive(false);
///////////////////////////////////////////////////////////////////////////////////////////////

    /*Gtk::MenuItem *menuitem_orders = Gtk::manage(new Gtk::MenuItem("_Orders", true));
    menubar->append(*menuitem_orders);
    Gtk::Menu *ordermenu = Gtk::manage(new Gtk::Menu());
    menuitem_orders->set_submenu(*ordermenu);

    Gtk::MenuItem *menuitem_order = Gtk::manage(new Gtk::MenuItem("_Place Order", true));
    menuitem_order->signal_activate().connect([this] {this->on_place_order_click();});
    ordermenu->append(*menuitem_order);

    Gtk::MenuItem *menuitem_listo = Gtk::manage(new Gtk::MenuItem("_List Orders", true));
    menuitem_listo->signal_activate().connect([this] {this->on_list_orders_click();});
    ordermenu->append(*menuitem_listo);*/

//////////////////////////////////////////////////////////////////////////////////////////////

    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("About", true));
    menuitem_about->signal_activate().connect([this] {this->on_about_click();});
    helpmenu->append(*menuitem_about);

/////////////////////////////////////////////////////////////////////////////////////////

    // /////////////
    // T O O L B A R
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);


    Gtk::ToolButton *new_store_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::HOME));
    new_store_button->set_tooltip_markup("New Store");
    new_store_button->signal_clicked().connect([this] {this->on_new_store_click();});
    Gtk::SeparatorToolItem *sep6 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep6);
    toolbar->append(*new_store_button);

    add_sweet_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::NEW));
    add_sweet_button->set_tooltip_markup("Add Sweet");
    add_sweet_button->signal_clicked().connect([this] {this->on_add_sweet_click();});
    Gtk::SeparatorToolItem *sep5 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep5);
    toolbar->append(*add_sweet_button);

    list_sweets_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::FIND));
    list_sweets_button->set_tooltip_markup("List Sweets");
    list_sweets_button->signal_clicked().connect([this] {this->on_list_sweets_click();});
    Gtk::SeparatorToolItem *sep4 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep4);
    toolbar->append(*list_sweets_button);
    list_sweets_button->set_sensitive(false);
/*
    *place_order_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::ADD));
    place_order_button->set_tooltip_markup("Place Order");
    place_order_button->signal_clicked().connect([this] {this->on_place_order_click();});
    Gtk::SeparatorToolItem *sep3 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep3);
    toolbar->append(*place_order_button);

    list_orders_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::PRINT));
    list_orders_button->set_tooltip_markup("List Orders");
    list_orders_button->signal_clicked().connect([this] {this->on_list_orders_click();});
    Gtk::SeparatorToolItem *sep2 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep2);
    toolbar->append(*list_orders_button);
    list_orders_button->set_sensitive(false);
*/
    Gtk::ToolButton *quit_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::QUIT));
    quit_button->set_tooltip_markup("Exit Shop");
    quit_button->signal_clicked().connect([this] {this->on_quit_click();});
    Gtk::SeparatorToolItem *sep = Gtk::manage(new Gtk::SeparatorToolItem());
    sep->set_expand(true);
    toolbar->append(*sep);
    toolbar->append(*quit_button);

//////////////////////////////////////////////////////////////////////////////////////////////////

    // ///////////////////////
    // D A T A   D I S P L A Y
    // Provide a text entry box to show the sweets and orders
    data = Gtk::manage(new Gtk::Label());
    data->set_hexpand(true);
    data->set_vexpand(true);
    vbox->add(*data);
    data->set_text("\t\tWelcome to Mav's Ultimate Sweet Shop!\n\n   Please click on the Store icon in order to get started");

    // ///////////////////////////////////
    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for transient messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->add(*msg);

    vbox->show_all();
}

//////////////////////////////////////////////////////////////

Mainwin::~Mainwin() { }

///////////////////////////////////////////////////////////////////
EntryDialog::EntryDialog(Gtk::Window& parent,
                         const Glib::ustring& message,
                         bool use_markup,
                         Gtk::MessageType type,
                         Gtk::ButtonsType buttons,
                         bool modal)
  : MessageDialog(parent, message, use_markup, type,buttons, modal), entry{new Gtk::Entry{}} {
    get_content_area()->pack_start(*entry);  // Add the entry to the MessageDialog
    entry->show();                           // Make the Entry visible
}

// Reflect the next two methods to their equivalents in the Entry widget
void EntryDialog::set_text (const Glib::ustring& text) {entry->set_text(text);}
Glib::ustring EntryDialog::get_text () const {return entry->get_text();}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////
// C A L L B A C K S
// /////////////////

void Mainwin::on_new_store_click()
{
  free(_store);
  _store = new Store();
  Gtk::MessageDialog{*this, "New Store added"}.run();
  msg->set_text("New Store !");
  data->set_text("You currently have " + std::to_string(this->_store->num_sweets()) + " sweets");

}


void Mainwin::on_add_sweet_click()
{
  std::string name = "";
  std::string price = "";
  double newprice;


  while (name == "")
  {
  EntryDialog edialog{*this, "Please enter the name of a sweet"};
  edialog.set_text("Enter the sweet name here");
  edialog.run();
  name = edialog.get_text();
}
 while(price == "")
  {
  EntryDialog qedialog{*this, "Please enter the " + name + " price" };
  qedialog.run();
  price = qedialog.get_text();
}
//try
//{
newprice = stof(price);
//}
//if (newprice == 0)
//{
  //std::throw newprice;
//}
//catch(newprice)
//(
  //Gtk::MessageDialog{*this, "Your sweet could not be added. Please try again"}.run();
//)
Sweet *candy = new Sweet(name,newprice);
  this->_store->add(*candy);
  msg->set_text("New Sweet added!");
  data->set_text("You currently have " + std::to_string(this->_store->num_sweets()) + " sweets");
  list_sweets_button->set_sensitive(true);
  menuitem_list_sweets->set_sensitive(true);
}


void Mainwin::on_list_sweets_click()
{
  int i;
  std::string name = "Here's a list of your Sweets\n\n\n";
  for (i = 0; i < this->_store->num_sweets(); i++)
  {
   name += "(" + this->_store->sweet(i).name() + "\t$";
   name += std::to_string(this->_store->sweet(i).price()) + ")" + "\n";
  }
  data->set_text(name);
  msg->set_text("Listed Sweets");
}
/*
void Mainwin::on_place_order_click()
{
  //Entry Dialog to select the name of the MenuItem
  //The name of the item will be added to the vector _order
  //The price will be added to the current price of the order with the
  //price oGtk::MessageDialog mdialog{*this, edialog.get_text()};f the selected item.
 //Store::add(Order& order) : _orders{order};
 msg->set_text("Order Placed!");
}

void Mainwin::on_list_orders_click()
{
  close();
}
*/
void Mainwin::on_about_click()
{
  Glib::ustring s = R"(
  <span size='24000' weight='bold'>Mav's Ultimate Sweet Shop</span>
  <span size='large'>Copyright 2019 by William Anderson</span>
  <span size='small'>Licensed under Creative Commons Attribution 4.0 International
  Icon created by the GNOME Project and XCF, used under free attribution license</span>

The user creates a new store by clicking File>New Store or adding a sweet. The user can create a sweet and enter its name and price by clicking Sweets>Add Sweet. The user may view their current sweets by clicking Sweets>List Sweet.
)";

  Gtk::MessageDialog dlg(*this, s, true, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
  dlg.run();
}

void Mainwin::on_quit_click()
{
  free (_store);
  close();
}

// /////////////////
// U T I L I T I E S
// /////////////////
