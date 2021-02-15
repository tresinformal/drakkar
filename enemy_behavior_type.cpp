#include "enemy_behavior_type.h"

#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>

void test_enemy_behavior_type()
{
  const enemy_behavior_type t{enemy_behavior_type::gezellig};
  const enemy_behavior_type u{enemy_behavior_type::shy};
  static_assert(t != u,"");
  {
    std::stringstream s;
    s << enemy_behavior_type::gezellig;

  }
  {
    std::cout << enemy_behavior_type::gezellig;
  }
  {
    std::stringstream s;
    s<< enemy_behavior_type::shy;
    // check that the string stream is not empty, i.e. it's shy now
    assert(!s.str().empty());
  }
  {
    //check that it is empty
    std::stringstream s;
    assert(s.str().empty());
  }

}

std::stringstream& operator << (std::stringstream &out, const enemy_behavior_type &enemy_type)
{

        if(enemy_type == enemy_behavior_type::gezellig)
        out << "gezillig";
        else if(enemy_type == enemy_behavior_type::shy)
        out << "shy";
        else
        out << "unknown";

    return out;
}
