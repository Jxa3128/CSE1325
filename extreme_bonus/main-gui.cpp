#include "mainwin.h"

int main (int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app =
     Gtk::Application::create(argc, argv, "edu.uta.cse1325.mvss");
 Mainwin win;
 win.set_title ("Mav's Ultimate Sweet Shop");
 return app->run(win);
}
