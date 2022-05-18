#include "key_action_map.h"

#include <SFML/System.hpp>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

key_action_map::key_action_map(
    const sf::Keyboard::Key& key_to_go_left,
    const sf::Keyboard::Key& key_to_go_right,
    const sf::Keyboard::Key& key_to_accelerate_forward,
    const sf::Keyboard::Key& key_to_accelerate_backward,
    const sf::Keyboard::Key& key_to_shoot,
    const sf::Keyboard::Key& key_to_stun
    ) : m_map {
{key_to_go_left, action_type::turn_left},
{key_to_go_right, action_type::turn_right},
{key_to_accelerate_forward, action_type::accelerate_forward},
{key_to_accelerate_backward, action_type::accelerate_backward},
{key_to_shoot, action_type::shoot},
{key_to_stun, action_type::shoot_stun_rocket}
          }
{
}

action_type key_action_map::to_action(sf::Keyboard::Key key) const noexcept
{
  if (has_key(key))
    {
      return m_map.find(key)->second;
    }
  return action_type::none;
}

sf::Keyboard::Key key_action_map::to_key(action_type action) const noexcept
{
  for (auto& it : m_map)
    {
      if (it.second == action)
        {
          return it.first;
        }
    }
  return sf::Keyboard::Key::Unknown;
}
bool key_action_map::has_key(sf::Keyboard::Key key) const noexcept
{
  if (m_map.find(key) != m_map.end())
    {
      return true;
    }

  return false;
}

bool operator==(const key_action_map& lhs, const key_action_map& rhs) noexcept
{
  return lhs.get_raw_map() == rhs.get_raw_map();
}

bool operator!=(const key_action_map& lhs, const key_action_map& rhs) noexcept
{
  return !(lhs.get_raw_map() == rhs.get_raw_map());
}

key_action_map get_player_1_kam()
{
  return key_action_map();
}

key_action_map get_player_2_kam()
{
  return key_action_map(
        sf::Keyboard::J,
        sf::Keyboard::L,
        sf::Keyboard::I,
        sf::Keyboard::K,
        //sf::Keyboard::Comma,
        sf::Keyboard::U,
        sf::Keyboard::O
        );
}
key_action_map get_player_3_kam()
{
  return key_action_map(
        sf::Keyboard::Left,
        sf::Keyboard::Right,
        sf::Keyboard::Up,
        sf::Keyboard::Down,
        //sf::Keyboard::Comma,
        sf::Keyboard::RControl,
        sf::Keyboard::Return
        );
}

sf::Keyboard::Key get_random_key()
{
  return static_cast<sf::Keyboard::Key>(std::rand() % 26);
}

key_action_map get_random_kam()
{
  std::vector<sf::Keyboard::Key> v_random_keys;
  while (v_random_keys.size() < 6)
    {
      sf::Keyboard::Key new_key = get_random_key();
      auto key_match = std::find(
            v_random_keys.begin(),
            v_random_keys.end(),
            new_key
            );
      if (key_match == v_random_keys.end())
      {
          v_random_keys.push_back(new_key);
      }
    }
  return key_action_map(
        v_random_keys[0],
      v_random_keys[1],
      v_random_keys[2],
      v_random_keys[3],
      v_random_keys[4],
      v_random_keys[5]
      );
}

std::vector<key_action_map> get_n_random_kams(int n)
{
  assert(n >= 0);
  std::vector<key_action_map> vector_kam;
  std::vector<sf::Keyboard::Key> storage_key;

  for(int i = 0; i != n; ++i){
    std::vector<sf::Keyboard::Key> v_random_keys;
    while (v_random_keys.size() < 6)
      {
        sf::Keyboard::Key new_key = get_random_key();
        auto key_match = std::find(
              storage_key.begin(),
              storage_key.end(),
              new_key
              );
        if (key_match == storage_key.end())
        {
            v_random_keys.push_back(new_key);
            storage_key.push_back(new_key);
        }

      }
    vector_kam.push_back(key_action_map(
                                        v_random_keys[0],
                                        v_random_keys[1],
                                        v_random_keys[2],
                                        v_random_keys[3],
                                        v_random_keys[4],
                                        v_random_keys[5]));
    }


  return vector_kam;
}



sf::Keyboard::Key get_stun_key(const key_action_map& m)
{
  return m.to_key(action_type::shoot_stun_rocket);
}

key_action_map load_kam(const std::string& filename)
{
  std::ifstream f(filename);
  key_action_map m;
  f >> m;
  return m;
}

void save_to_file(const key_action_map& kam, const std::string& filename)
{
  std::ofstream file(filename);
  file << kam;
}

sf::Keyboard::Key to_sfml_key(const std::string& s)
{
  if (s == "A") return sf::Keyboard::Key::A;
  if (s == "B") return sf::Keyboard::Key::B;
  if (s == "C") return sf::Keyboard::Key::C;
  if (s == "D") return sf::Keyboard::Key::D;
  if (s == "E") return sf::Keyboard::Key::E;
  if (s == "F") return sf::Keyboard::Key::F;
  if (s == "G") return sf::Keyboard::Key::G;
  if (s == "H") return sf::Keyboard::Key::H;
  if (s == "I") return sf::Keyboard::Key::I;
  if (s == "J") return sf::Keyboard::Key::J;
  if (s == "K") return sf::Keyboard::Key::K;
  if (s == "L") return sf::Keyboard::Key::L;
  if (s == "M") return sf::Keyboard::Key::M;
  if (s == "N") return sf::Keyboard::Key::N;
  if (s == "O") return sf::Keyboard::Key::O;
  if (s == "P") return sf::Keyboard::Key::P;
  if (s == "Q") return sf::Keyboard::Key::Q;
  if (s == "R") return sf::Keyboard::Key::R;
  if (s == "S") return sf::Keyboard::Key::S;
  if (s == "T") return sf::Keyboard::Key::T;
  if (s == "U") return sf::Keyboard::Key::U;
  if (s == "V") return sf::Keyboard::Key::V;
  if (s == "W") return sf::Keyboard::Key::W;
  if (s == "X") return sf::Keyboard::Key::X;
  if (s == "Y") return sf::Keyboard::Key::Y;
  if (s == "Z") return sf::Keyboard::Key::Z;

  if (s != " ") std::clog << "UNKNOWN KEY: " << s << '\n';

  assert(s == " "); // Or the key has not been encoded yet
  return sf::Keyboard::Key::Space;

}

std::string to_str(const sf::Keyboard::Key key)
{
  switch (key)
  {
    case sf::Keyboard::Key::A: return "A";
    case sf::Keyboard::Key::B: return "B";
    case sf::Keyboard::Key::C: return "C";
    case sf::Keyboard::Key::D: return "D";
    case sf::Keyboard::Key::E: return "E";
    case sf::Keyboard::Key::F: return "F";
    case sf::Keyboard::Key::G: return "G";
    case sf::Keyboard::Key::H: return "H";
    case sf::Keyboard::Key::I: return "I";
    case sf::Keyboard::Key::J: return "J";
    case sf::Keyboard::Key::K: return "K";
    case sf::Keyboard::Key::L: return "L";
    case sf::Keyboard::Key::M: return "M";
    case sf::Keyboard::Key::N: return "N";
    case sf::Keyboard::Key::O: return "O";
    case sf::Keyboard::Key::P: return "P";
    case sf::Keyboard::Key::Q: return "Q";
    case sf::Keyboard::Key::R: return "R";
    case sf::Keyboard::Key::S: return "S";
    case sf::Keyboard::Key::T: return "T";
    case sf::Keyboard::Key::U: return "U";
    case sf::Keyboard::Key::V: return "V";
    case sf::Keyboard::Key::W: return "W";
    case sf::Keyboard::Key::X: return "X";
    case sf::Keyboard::Key::Y: return "Y";
    case sf::Keyboard::Key::Z: return "Z";
    default: break;
  }

  // Or maybe the key is not present yet in the
  // switch statement above :-)
  assert(key == sf::Keyboard::Key::Space);
  return " ";
}

std::string to_str(const key_action_map& kam) noexcept
{
  std::stringstream s;
  for (const auto& p: kam.get_raw_map()) {
    s << to_str(p.first) << " " << p.second << " ";
  };
  std::string t = s.str();
  // Remove the space at the end
  t.pop_back();
  return t;
}

std::istream& operator>>(std::istream& is, key_action_map& kam)
{
  std::string action = "dummy"; // In istream for readability

  // Go through each key action pair, check if the order is correct
  std::string key_to_go_left;
  is >> key_to_go_left >> action;
  assert(to_str(action_type::turn_left) == action);

  std::string key_to_go_right;
  is >> key_to_go_right >> action;
  assert(to_str(action_type::turn_right) == action);

  std::string key_to_stun;
  is >> key_to_stun >> action;
  assert(to_str(action_type::shoot_stun_rocket) == action);

  std::string key_to_shoot;
  is >> key_to_shoot >> action;
  assert(to_str(action_type::shoot) == action);

  std::string key_to_accelerate_backward;
  is >> key_to_accelerate_backward >> action;
  assert(to_str(action_type::accelerate_backward) == action);

  std::string key_to_accelerate_forward;
  is >> key_to_accelerate_forward >> action;
  assert(to_str(action_type::accelerate_forward) == action);


  const key_action_map m(
    to_sfml_key(key_to_go_left),
    to_sfml_key(key_to_go_right),
    to_sfml_key(key_to_accelerate_forward),
    to_sfml_key(key_to_accelerate_backward),
    to_sfml_key(key_to_shoot),
    to_sfml_key(key_to_stun)
  );
  kam = m;
  return is;
}

std::ostream& operator<<(std::ostream& os, const key_action_map& kam)
{
  os << to_str(kam);
  return os;
}



void test_key_action_map()//!OCLINT tests can be many
{
#ifndef NDEBUG // no tests in release
  //It is possible to return an action type from a key being pressed
  //The keys are for now the ones pressed by player1 (position 0 in the player index)
  {
    const key_action_map m; //Use player 1 as default for now
    assert(m.to_action(sf::Keyboard::A) == action_type::turn_left);
    assert(m.to_action(sf::Keyboard::D) == action_type::turn_right);
    assert(m.to_action(sf::Keyboard::W) == action_type::accelerate_forward);
    assert(m.to_action(sf::Keyboard::S) == action_type::accelerate_backward);
    assert(m.to_action(sf::Keyboard::Q) == action_type::shoot);
    assert(m.to_action(sf::Keyboard::E) == action_type::shoot_stun_rocket);
  }
  {
    const key_action_map m = get_player_1_kam();
    assert(m.to_action(sf::Keyboard::A) == action_type::turn_left);
    assert(m.to_action(sf::Keyboard::D) == action_type::turn_right);
    assert(m.to_action(sf::Keyboard::W) == action_type::accelerate_forward);
    assert(m.to_action(sf::Keyboard::S) == action_type::accelerate_backward);
    assert(m.to_action(sf::Keyboard::Q) == action_type::shoot);
  }
  {
    const sf::Keyboard::Key key_to_go_left = sf::Keyboard::C;
    const sf::Keyboard::Key key_to_go_right = sf::Keyboard::B;
    const sf::Keyboard::Key key_to_accelerate_forward = sf::Keyboard::A;
    const sf::Keyboard::Key key_to_accelerate_backward = sf::Keyboard::Z;
    const sf::Keyboard::Key key_to_shoot = sf::Keyboard::E;
    const key_action_map m(
          key_to_go_left,
          key_to_go_right,
          key_to_accelerate_forward,
          key_to_accelerate_backward,
          key_to_shoot
          );
    assert(m.to_action(key_to_go_left) == action_type::turn_left);
    assert(m.to_action(key_to_go_right) == action_type::turn_right);
    assert(m.to_action(key_to_accelerate_forward) == action_type::accelerate_forward);
    assert(m.to_action(key_to_accelerate_backward) == action_type::accelerate_backward);
    assert(m.to_action(key_to_shoot) == action_type::shoot);
  }
  {
    const key_action_map m = get_player_2_kam();
    assert(m.to_action(sf::Keyboard::J) == action_type::turn_left);
    assert(m.to_action(sf::Keyboard::L) == action_type::turn_right);
    assert(m.to_action(sf::Keyboard::I) == action_type::accelerate_forward);
    assert(m.to_action(sf::Keyboard::K) == action_type::accelerate_backward);
    assert(m.to_action(sf::Keyboard::U) == action_type::shoot);
  }
  {
    const key_action_map m = get_player_1_kam();
    assert( m.has_key(sf::Keyboard::A));
    assert( m.has_key(sf::Keyboard::D));
    assert( m.has_key(sf::Keyboard::W));
    assert( m.has_key(sf::Keyboard::S));
    assert( m.has_key(sf::Keyboard::Q));
    assert(!m.has_key(sf::Keyboard::L));
  }

  //Giving a key that is not in the map returns a action_type::none action
  //but does not crash the program
  {
    const key_action_map m = get_player_1_kam();
    assert(!m.has_key(sf::Keyboard::L));
    assert(action_type::none == m.to_action(sf::Keyboard::L));

  }
#define FIX_ISSUE_282
#ifdef FIX_ISSUE_282
  // operator==
  {
    const key_action_map a = get_player_1_kam();
    const key_action_map b = get_player_1_kam();
    const key_action_map c = get_player_3_kam();
    assert(a == b);
    assert(b == a);
    assert(!(a == c));
    assert(!(b == c));
  }
#endif // FIX_ISSUE_282

  // operator!=
  {
    const key_action_map a = get_player_1_kam();
    const key_action_map b = get_player_1_kam();
    const key_action_map c = get_player_3_kam();
    assert(!(a != b));
    assert(!(b != a));
    assert(a != c);
    assert(b != c);
  }

#define FIX_ISSUE_282
#ifdef FIX_ISSUE_282
  {
    const int rng_seed = 271;
    std::srand(rng_seed);
    sf::Keyboard::Key a = get_random_key();
    sf::Keyboard::Key b = get_random_key();
    assert(a != b);
    std::srand(rng_seed);
    sf::Keyboard::Key c = get_random_key();
    assert(a == c);
    const int other_seed = 111;
    std::srand(other_seed);
    sf::Keyboard::Key d = get_random_key();
    assert(a != d);
  }
  {
    const int rng_seed = 271;
    std::srand(rng_seed);
    // random keyboards - delete this test when issue 303 is closed
    key_action_map a = get_random_kam();
    key_action_map b = get_random_kam();
    assert(a != b);
    std::srand(rng_seed);
    key_action_map c = get_random_kam();
    assert(a == c);
    const int other_seed = 111;
    std::srand(other_seed);
    key_action_map d = get_random_kam();
    assert(a != d);
  }
#endif // FIX_ISSUE_303
#endif

 #define FIX_ISSUE_304
//#ifdef FIX_ISSUE_304
    //Get the stun key (Num1 by default)
    {
        const key_action_map m = get_player_1_kam();
        assert(get_stun_key(m) == sf::Keyboard::E);
    }
//#endif // FIX_ISSUE_304

#define FIX_ISSUE_355
#ifdef FIX_ISSUE_355
  {
    const key_action_map kam = get_player_1_kam();
    assert(kam.to_key(action_type::turn_left) == sf::Keyboard::A);
    assert(kam.to_key(action_type::turn_right) == sf::Keyboard::D);
    assert(kam.to_key(action_type::accelerate_forward) == sf::Keyboard::W);
    assert(kam.to_key(action_type::accelerate_backward) == sf::Keyboard::S);
    assert(kam.to_key(action_type::shoot) == sf::Keyboard::Q);
    assert(kam.to_key(action_type::shoot_stun_rocket) == sf::Keyboard::E);
  }
#endif // FIX_ISSUE_355
  // 522. operator<< for key_action_map
  {
    const key_action_map kam = get_player_1_kam();
    std::stringstream s;
    s << kam;
  }
  // 522. Can save and load a key_action_map
  {
    const key_action_map kam = get_player_1_kam();
    const std::string filename = "test.txt";
    save_to_file(kam, filename);
    const key_action_map map_again = load_kam(filename);
    assert(kam == map_again);
    std::remove(filename.c_str());
  }
  #ifdef FIX_ISSUE_522
  // 522. Can save and load a key_action_map for player 2
  {
    const key_action_map kam = get_player_2_kam();
    const std::string filename = "test.txt";
    save_to_file(kam, filename);
    const key_action_map map_again = load_kam(filename);
    assert(kam == map_again);
    std::remove(filename.c_str());
  }
  // 522. Can save and load a key_action_map for player 3
  {
    const key_action_map kam = get_player_3_kam();
    const std::string filename = "test.txt";
    save_to_file(kam, filename);
    const key_action_map map_again = load_kam(filename);
    assert(kam == map_again);
    std::remove(filename.c_str());
  }
  #endif // FIX_ISSUE_522

}
