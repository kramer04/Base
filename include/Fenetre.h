#ifndef FENETRE_H
#define FENETRE_H

#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/buttonbox.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/messagedialog.h>
#include <gtkmm-3.0/gtkmm/stock.h>
#include <string>

class Fenetre : public Gtk::Window
{
public:
  Fenetre();

private:
  Gtk::VBox boiteV;
  Gtk::ButtonBox boutonBox;
  Gtk::Box hbox1, hbox2, hbox3;
  Gtk::Button resultat, quit, efface;
  Gtk::Label un, deux, trois;
  Gtk::Entry zoneBase, zoneNombre, zoneResultat;

  void quitte();
  void affiche_resultat();
  void max16();
  void min_max_long();
  void clear();
};
#endif