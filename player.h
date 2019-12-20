#ifndef PLAYER_H
#define PLAYER_H

#include "action_type.h"
#include "color.h"
#include "player_shape.h"
#include <cmath>

class player
{
public:
  player(const double x = 0.0, const double y = 0.0,
         const player_shape shape = player_shape::rocket,
         const double player_speed = 0, const double player_max_speed = 2,
         const double player_acceleration = 0.1,
         const double player_deceleration = 0.001, const double size = 100.0,
         const double direction = 0.0, const double turn_rate = 0.1,
         const color &any_color = color());

  /// Get the color of the player
  const color &get_color() const noexcept { return m_color; }

  /// Get the X coordinat of the player
  double get_x() const noexcept { return m_x; }

  /// Get the Y coordinat of the player
  double get_y() const noexcept { return m_y; }

  /// Get the shape of the player
  player_shape get_shape() const noexcept { return m_shape; }

  /// Get the size of the player
  double get_size() const noexcept { return m_size; }

  /// Get the speed of the player
  double get_speed() const noexcept { return m_player_speed; }

  /// Get the speed of the player
  double get_max_s() const noexcept { return m_player_max_speed; }

  /// Get the acceleration of the player
  double get_acceleration() const noexcept { return m_player_acceleration; }

  /// Get the direction of player movement
  double get_direction() const noexcept { return m_direction; }

  /// Get the player's health
  double get_health() const noexcept { return m_health; }

  /// makes the player in the game execute an action
  void do_action(action_type action);

  /// Turn the player left
  void turn_left() noexcept { m_direction += m_turn_rate; }

  /// Turn the player right
  void turn_right() noexcept { m_direction -= m_turn_rate; }

  /// Update the position of the player on the base of its speed and direction
  void update_player_position() noexcept
  {
    m_x += cos(m_direction) * m_player_speed;
    m_y += sin(m_direction) * m_player_speed;
  }

  /// Accelerate the player
  void accelerate() noexcept;

  /// Brake/decelerate the player
  void brake() noexcept;

private:
  /// The player's color, will change depending on food items
  color m_color;

  /// The X coordinat of the player
  double m_x;

  /// The Y coordinat of the player
  double m_y;

  /// The shape of the player
  player_shape m_shape;

  /// The speed of the player
  double m_player_speed;

  /// The maximum speed of the player
  double m_player_max_speed;

  /// The acceleration of the player
  double m_player_acceleration;

  /// The acceleration of the player
  double m_player_deceleration;

  /// The size of the player
  double m_size;

  /// The direction of player in radiants
  double m_direction;

  /// The rate at which the player turns
  double m_turn_rate;

  /// Player's health percentage, the player always start with max health at
  /// construction
  double m_health = 1.0;
};

/// Get the blueness (from the color) of the player
int get_blueness(const player& p) noexcept;

/// Get the greenness (from the color) of the player
int get_greenness(const player& p) noexcept;

/// Get the redness (from the color) of the player
int get_redness(const player& p) noexcept;

/// Test the player class
void test_player();

#endif // PLAYER_H
