#include "key_action_map.h"
#include <cassert>

key_action_map::key_action_map(
    const sf::Keyboard::Key& key_to_go_left,
    const sf::Keyboard::Key& key_to_go_right,
    const sf::Keyboard::Key& key_to_accelerate,
    const sf::Keyboard::Key& key_to_brake,
    const sf::Keyboard::Key& key_to_shoot,
    const sf::Keyboard::Key& key_to_stun
    ) : m_map {
{key_to_go_left, action_type::turn_left},
{key_to_go_right, action_type::turn_right},
{key_to_accelerate, action_type::accelerate},
{key_to_brake, action_type::brake},
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

sf::Keyboard::Key get_stun_key(const key_action_map& m)
{
  return m.to_key(action_type::shoot_stun_rocket);
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
    assert(m.to_action(sf::Keyboard::W) == action_type::accelerate);
    assert(m.to_action(sf::Keyboard::S) == action_type::brake);
    assert(m.to_action(sf::Keyboard::Q) == action_type::shoot);
    assert(m.to_action(sf::Keyboard::E) == action_type::shoot_stun_rocket);
  }
  {
    const key_action_map m = get_player_1_kam();
    assert(m.to_action(sf::Keyboard::A) == action_type::turn_left);
    assert(m.to_action(sf::Keyboard::D) == action_type::turn_right);
    assert(m.to_action(sf::Keyboard::W) == action_type::accelerate);
    assert(m.to_action(sf::Keyboard::S) == action_type::brake);
    assert(m.to_action(sf::Keyboard::Q) == action_type::shoot);
  }
  {
    const sf::Keyboard::Key key_to_go_left = sf::Keyboard::C;
    const sf::Keyboard::Key key_to_go_right = sf::Keyboard::B;
    const sf::Keyboard::Key key_to_accelerate = sf::Keyboard::A;
    const sf::Keyboard::Key key_to_brake = sf::Keyboard::Z;
    const sf::Keyboard::Key key_to_shoot = sf::Keyboard::E;
    const key_action_map m(
          key_to_go_left,
          key_to_go_right,
          key_to_accelerate,
          key_to_brake,
          key_to_shoot
          );
    assert(m.to_action(key_to_go_left) == action_type::turn_left);
    assert(m.to_action(key_to_go_right) == action_type::turn_right);
    assert(m.to_action(key_to_accelerate) == action_type::accelerate);
    assert(m.to_action(key_to_brake) == action_type::brake);
    assert(m.to_action(key_to_shoot) == action_type::shoot);
  }
  {
    const key_action_map m = get_player_2_kam();
    assert(m.to_action(sf::Keyboard::J) == action_type::turn_left);
    assert(m.to_action(sf::Keyboard::L) == action_type::turn_right);
    assert(m.to_action(sf::Keyboard::I) == action_type::accelerate);
    assert(m.to_action(sf::Keyboard::K) == action_type::brake);
    //assert(m.to_action(sf::Keyboard::Comma) == action_type::acc_backward);
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
    assert(kam.to_key(action_type::accelerate) == sf::Keyboard::W);
    assert(kam.to_key(action_type::brake) == sf::Keyboard::S);
    assert(kam.to_key(action_type::shoot) == sf::Keyboard::Q);
    assert(kam.to_key(action_type::shoot_stun_rocket) == sf::Keyboard::E);
  }
#endif // FIX_ISSUE_355
}
