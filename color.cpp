#include "color.h"

#include <cassert>
#include <cstdlib>
#include <sstream>
#include <iostream>

color::color(const int r, const int g, const int b, const int a)
    : m_r{r}, m_g{g}, m_b{b}, m_a{a}
{
    // Stub, need exceptions later
    assert(m_r >= 0);
    assert(m_r <= 255);
    assert(m_g >= 0);
    assert(m_g <= 255);
    assert(m_g <= 256);
    assert(m_b >= 0);
    assert(m_b <= 255);
    assert(m_a >= 0);
    assert(m_a <= 255);
}


int get_blueness(const color &c) noexcept { return c.get_blue(); }

int get_greenness(const color &c) noexcept { return c.get_green(); }

int get_opaqueness(const color &c) noexcept { return c.get_opaqueness(); }

int get_redness(const color &c) noexcept { return c.get_red(); }

//convert color to string in debugging purposes
std::string to_str(const color& in_color) noexcept
{
    std::string msg = "[";
    msg+=std::to_string(in_color.get_red())+", ";
    msg+=std::to_string(in_color.get_green())+", ";
    msg+=std::to_string(in_color.get_blue())+", ";
    msg+=std::to_string(in_color.get_opaqueness())+"]";
    return msg;
}


void test_color()
{
    #ifndef NDEBUG // no tests is release
    // Color is white by default
    {
        const color c;
        assert(c.get_red() == 255);
        assert(c.get_green() == 255);
        assert(c.get_blue() == 255);
        assert(c.get_opaqueness() == 255);
    }
    // Test get functions
    {
        const color c1{0,21,255,10};
        assert(get_redness(c1)==0);
        assert(get_greenness(c1)==21);
        assert(get_blueness(c1)==255);
        assert(get_opaqueness(c1)==10);
    }
    // operator==
    {
        const color c;
        const color c1;
        assert(c == c1);
    }

//     operator!=
    {
      const color red{255, 0, 0};
      const color green{0, 255, 0};
      assert(red != green);
    }
    // operator<<
    {
        std::stringstream s;
        const color c;
        s << c;
    }
    {
        const color c;
        std::cout << c;
    }
  //#define FIX_ISSUE_322
  #ifdef FIX_ISSUE_322
  // Colors have the correct RGB values
  {
    const color red = create_red_color();
    assert(get_redness(red) == 255);
    assert(get_greenness(red) == 0);
    assert(get_blueness(red) == 0);
  }
  {
    const color green = create_green_color();
    assert(get_redness(green) == 0);
    assert(get_greenness(green) == 255);
    assert(get_blueness(green) == 0);
  }
  {
    const color blue = create_blue_color();
    assert(get_redness(blue) == 0);
    assert(get_greenness(blue) == 0);
    assert(get_blueness(blue) == 255);
  }
  #endif // FIX_ISSUE_322

  //#define FIX_ISSUE_230
  #ifdef FIX_ISSUE_230
  // The correct color must win
  {
    const color paper = create_red_color();
    const color rock = create_green_color();
    const color scissors = create_blue_color();
    assert(is_first_color_winner(paper, rock));
    assert(is_first_color_winner(scissors, paper));
    assert(is_first_color_winner(rock, scissors));
    assert(!is_first_color_winner(rock, paper));
    assert(!is_first_color_winner(paper, scissors));
    assert(!is_first_color_winner(scissors, rock));
  }
  #endif // FIX_ISSUE_230


#endif // NDEBUG
}

bool operator==(const color& lhs, const color& rhs) noexcept
{
    return lhs.get_red() == rhs.get_red()
            && lhs.get_green() == rhs.get_green()
            && lhs.get_blue() == rhs.get_blue()
            && lhs.get_opaqueness() == rhs.get_opaqueness()
            ;
}

bool operator!=(const color& lhs, const color& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& operator << (std::ostream &out, const color &color)
{
    out << "Color(" << std::to_string(color.get_red()) <<
           ", " << std::to_string(color.get_green()) <<
           ", " << std::to_string(color.get_blue()) <<
           ")";

    return out;
}
