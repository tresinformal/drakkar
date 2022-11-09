#ifndef ABOUT_H
#define ABOUT_H

#include <string>
#include <vector>

/// Contains the information about the game
/// This class is displayed by the 'about_view' class
class about
{
public:
  about();

  /// Get a list of all the contributors
  std::vector<std::string> get_contributors() const noexcept;
};

void test_about();

#endif // ABOUT_H
