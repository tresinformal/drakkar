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
    "Ludvig"
  };
}

void test_about()
{
  // The About object contains a list of contributors
  {
    about ab;
    std::vector<std::string> contributors = ab.get_contributors();
  }
#ifdef FIX_ISSUE_600
  // (600) The list of contributors is up-to-date
  {
    // need to learn about how to fetch info from github for this
  }
#endif

#ifdef FIX_ISSUE_596
  // (596) The About object keeps track of the game version
  {
    about ab;
    std::vector<std::string> version;
    version = ab.get_version();
  }
#endif

#ifdef FIX_ISSUE_597
  // (597) The game version is up-to-date
  {
    // need to learn about how to fetch info from github for this
  }
#endif

#ifdef FIX_ISSUE_599
  // (599) The About object has a link to the GitHub repo
  {
    about ab;
    std::vector<std::string> link_to_gh;
    link_to_gh = ab.get_link_repo();
  }
#endif

#ifdef FIX_ISSUE_598
  // (598) The About object has a link to the Discord
  {
    about ab;
    std::vector<std::string> link_to_discord;
    link_to_discord = ab.get_link_discord();
  }
#endif

}
