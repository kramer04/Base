#include "Fenetre.h"
#include <limits>
#include <stdexcept>
#include <iostream>

Fenetre::Fenetre() : boiteV(true, 15), boutonBox(Gtk::ORIENTATION_HORIZONTAL),
                     hbox1(Gtk::ORIENTATION_HORIZONTAL), hbox2(Gtk::ORIENTATION_HORIZONTAL), hbox3(Gtk::ORIENTATION_HORIZONTAL),
                     resultat("Résultat"), quit(Gtk::Stock::QUIT), efface("Clear"),
                     un("Un nombre \nentier"), deux("base min 2\nmax 16"), trois("Résultat")
{
  set_title("Calcul sur les bases");
  set_border_width(5);
  set_default_size(420, 200);
  set_position(Gtk::WIN_POS_CENTER);
  set_icon_from_file("base.png");

  zoneBase.set_alignment(GDK_KEY_Right);
  zoneNombre.set_alignment(GDK_KEY_Right);
  zoneResultat.set_editable(false);
  zoneResultat.set_alignment(GDK_KEY_Right);

  add(boiteV);

  hbox2.pack_start(un);
  hbox2.pack_start(zoneNombre);
  hbox1.pack_start(deux);
  hbox1.pack_start(zoneBase);
  hbox3.pack_start(trois);
  hbox3.pack_start(zoneResultat);
  boiteV.pack_start(hbox2, Gtk::PACK_SHRINK);
  boiteV.pack_start(hbox1, Gtk::PACK_SHRINK);
  boiteV.pack_start(hbox3, Gtk::PACK_SHRINK);
  boiteV.pack_start(boutonBox, Gtk::PACK_SHRINK);
  boutonBox.pack_start(resultat, Gtk::PACK_SHRINK);
  boutonBox.pack_start(efface, Gtk::PACK_SHRINK);
  boutonBox.pack_start(quit, Gtk::PACK_SHRINK);

  quit.signal_clicked().connect([this]() { quitte(); });
  resultat.signal_clicked().connect([this]() { affiche_resultat(); });
  //zoneBase.signal_key_press_event().connect([&](GdkEventKey *event) -> bool {std::cout<<"pressed :"<<std::hex<<event->keyval<<" "<<std::hex<<event->state<<std::endl;return false; }, false);
  zoneBase.signal_activate().connect([this]() { affiche_resultat(); });
  zoneNombre.signal_activate().connect([this]() { affiche_resultat(); });
  efface.signal_clicked().connect([this]() { clear(); });

  show_all();
}
void Fenetre::quitte()
{
  hide();
}
void Fenetre::affiche_resultat()
{
  std::string base{zoneBase.get_text()}, nombre{zoneNombre.get_text()}, strResultat{};
  ulong resultat{0}, b{0}, nb{0};

  try
  {
    resultat = std::stoul(nombre);
    b = std::stoul(base);

    char a{0};

    if (b < 2 || b > 16)
    {
      max16();
    }
    else
    {
      while (resultat > 0)
      {
        nb = resultat % b;
        if (nb > 9)
        {
          a = 55 + nb;
          strResultat = a + strResultat;
        }
        else
        {
          strResultat = std::to_string(nb) + strResultat;
        }
        resultat /= b;
      }
      zoneResultat.set_text(strResultat);
    }
  }
  catch (std::overflow_error &exception)
  {
    std::cout << "Erreur overflow_error " << exception.what() << std::endl;
  }
  catch (std::runtime_error &exception)
  {
    std::cout << "Erreur runtime_error " << exception.what() << std::endl;
  }
  catch (std::out_of_range &exception)
  {
    std::cout << "Chaîne trop longue " << exception.what() << std::endl;
    min_max_long();
  }
  catch (std::invalid_argument &exception)
  {
    std::cout << "Argument invalide " << exception.what() << std::endl;
    zoneNombre.grab_focus();
  }
  catch (std::logic_error &exception)
  {
    std::cout << "Erreur logic_error " << exception.what() << std::endl;
  }
  catch (std::exception &exception)
  {
    std::cout << "Erreur exception " << exception.what() << std::endl;
  }
}

void Fenetre::max16()
{
  Gtk::MessageDialog dialogue(*this, "<big><b><i>Attention</i> Base min 2 max 16.</b></big>", true, Gtk::MESSAGE_WARNING);
  dialogue.set_title("Alerte");
  dialogue.run();
  zoneResultat.set_text("");
  zoneBase.grab_focus();
}
void Fenetre::min_max_long()
{
  Gtk::MessageDialog dialogue(*this, "<big><b><i>Attention</i>\nmin 0\nmax 18446744073709551615.</b></big>", true, Gtk::MESSAGE_WARNING);
  dialogue.set_title("Alerte dépassement");
  dialogue.run();
  zoneNombre.grab_focus();
}
void Fenetre::clear()
{
  zoneBase.set_text("");
  zoneNombre.set_text("");
  zoneResultat.set_text("");
  zoneNombre.grab_focus_without_selecting();
}