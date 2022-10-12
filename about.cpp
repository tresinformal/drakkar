#include "about.h"

about::about()
{

}

std::vector<std::string> about::get_contributors() const noexcept
{
  // Ordered by list at
  // https://github.com/tresinformal/game/graphs/contributors
  return
  {
    "Richel Bilderbeek",
    "Theo Pannetier",
    "Stefano Tiso",
    "Oliver Turner",
    "Sebastian Mader",
    "Pavel Dyakonov",
    "Pedro Neves",
    "Kristiina Ausmees",
    "Aparajitha 'Apu' Ramesh",
    "Giorgio Boccarella",
    "Clem Carle",
    "Claudio Tiecher",
    "Georgia Tsaridou",
    "Xiaoyan Long",
    "Chris Hesper",
    "Manuel",
    "Ines Daras",
    "Johanna Tingvall-Gustafsson",
    "Joshua Lambert",
    "Kirsten Ferwerda",
    "Tim Temizyuerek",
    "Jan Derk Kotlarski",
    "Timo van Eldijk",
    "Paula",
    "Sergio Gonmoll",
    "Marina Papadopoulou",
    "Oscar Gullberg"
  };
}
