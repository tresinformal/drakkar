#include "color.h"

#include <cassert>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>

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

color create_red_color()
{
  return color(255, 0, 0, 255);
}

color create_green_color()
{
  return color(0, 255, 0, 255);
}

color create_blue_color()
{
  return color(0, 0, 255, 255);
}

color create_white_color()
{
  return color(255, 255, 255, 255);
}

color create_black_color()
{
  return color(0, 0, 0, 255);
}

color get_random_respawn_color(std::mt19937& rng)
{
    std::uniform_int_distribution<> dis(0, 2);
    switch(dis(rng))
    {
        case 0:
            return create_red_color();
        case 1:
            return create_blue_color();
        case 2: default:
            return create_green_color();
    }
}

double calc_hue(const color &c)
{
  double r = c.get_red()   / 255.0;
  double g = c.get_green() / 255.0;
  double b = c.get_blue()  / 255.0;
  double max_val = std::max(std::max(r, g), b);
  double min_val = std::min(std::min(r, g), b);
  double hue;

  if (max_val == min_val)
    {
      hue = 0.0;
    }
  else if (max_val == r)
    {
      hue = 0.0 + (g - b) / (max_val - min_val);
      if (hue < 0.0)
        {
          hue += 6.0;
        }
    }
  else if (max_val == g)
    {
      hue = 2.0 + (b - r) / (max_val - min_val);
    }
  else
    {
      hue = 4.0 + (r - g) / (max_val - min_val);
    }
  return hue * 60.0;
}

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

bool is_first_color_winner(const color& c1, const color& c2)
{
  double hue1 = calc_hue(c1);
  double hue2 = calc_hue(c2);

  return (hue1 == 0.0 && hue2 == 120.0) || (hue1 == 120.0 && hue2 == 240.0) || (hue1 == 240.0 && hue2 == 0.0);
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

  // operator!=
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
    assert(!s.str().empty());
  }
  // Colors have the correct RGB values
  {
    //  This is ISSUE_#322
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


  // Colors have the correct hues
  // See http://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/
  {
    //  This is ISSUE_#229
    const color red = create_red_color();
    assert(calc_hue(red) == 0.0);
  }
  {
    const color green = create_green_color();
    assert(calc_hue(green) == 120.0);
  }
  {
    const color blue = create_blue_color();
    assert(calc_hue(blue) == 240.0);
  }

  // The correct color must win
  {
    //  This is ISSUE_#230
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

  //#define FIX_ISSUE_448
#ifdef FIX_ISSUE_448
  // #448 Colors from class color can be converted to SFML's sf::Color class
  {
    const color c1{0, 21, 255, 10};
    sf::Color c2{0, 21, 255, 10};
    assert(to_sf_color(c1) == c2);
  }
#endif // FIX_ISSUE_448

  // #460 Ready-made black and white colors are available
  {
    const color black = create_black_color();
    assert(get_redness(black) == 0);
    assert(get_greenness(black) == 0);
    assert(get_blueness(black) == 0);
  }
  {
    const color white = create_white_color();
    assert(get_redness(white) == 255);
    assert(get_greenness(white) == 255);
    assert(get_blueness(white) == 255);
  }

  #define FIX_ISSUE_628
  #ifdef FIX_ISSUE_628
  // (628) A random color between red, blue, green can be sampled
  {
    const color r = create_red_color();
    const color g = create_green_color();
    const color b = create_blue_color();

    const int a_seed{42};
    std::mt19937 rng1(a_seed);
    const color a_color = get_random_respawn_color(rng1);
    assert(a_color == r || a_color == g || a_color == b);

    const int another_seed{43}; /// please change seed if draws same color as 42
    std::mt19937 rng2(another_seed);
    const color another_color = get_random_respawn_color(rng2);
    assert(another_color == r || another_color == g || another_color == b);
    assert(a_color != another_color);

    const int same_seed = a_seed;
    std::mt19937 rng3(same_seed);
    const color same_color = get_random_respawn_color(rng3);
    assert(same_color == a_color);
  }
#endif // FIX_ISSUE_628

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
  out << "Color " << std::to_string(color.get_red()) <<
         " " << std::to_string(color.get_green()) <<
         " " << std::to_string(color.get_blue()) << "\n";
  return out;
}
