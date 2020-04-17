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
         const double player_deceleration = -0.001,
         const double player_acc_backward = -0.01,
         const double size = 100.0,
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

  /// Get the radius of the player
  double get_radius() const noexcept { return m_radius; }

  /// Get the speed of the player
  double get_speed() const noexcept { return m_player_speed; }

  /// Get the speed of the player
  double get_max_s() const noexcept { return m_player_max_speed; }

  /// Get the acceleration of the player
  double get_acceleration() const noexcept { return m_player_acceleration; }

  /// Get the direction of player movement, in radians
  double get_direction() const noexcept { return m_direction_radians; }

  /// Get the player's health
  double get_health() const noexcept { return m_health; }

  /// Is the player shooting?
  /// When a player shoots, 'm_is_shooting' is true for one tick.
  /// 'game' reads 'm_is_shooting' and if it is true,
  /// it (1) creates a projectile, (2) sets 'm_is_shooting' to false
  bool is_shooting() const noexcept { return m_is_shooting; }

  /// Set the color of the player
  void set_color(const color &c) noexcept { m_color = c; }

  /// The player shoots, does nothing for now
  /// When a player shoots, 'm_is_shooting' is true for one tick.
  /// 'game' reads 'm_is_shooting' and if it is true,
  /// it (1) creates a projectile, (2) sets 'm_is_shooting' to false
  void shoot() noexcept { m_is_shooting = true; }

  /// Make the player stop shooting
  /// When a player shoots, 'm_is_shooting' is true for one tick.
  /// 'game' reads 'm_is_shooting' and if it is true,
  /// it (1) creates a projectile, (2) makes the player stop shooting
  void stop_shooting() noexcept { m_is_shooting = false; }

  /// Set a player x position
  void set_x(double x) noexcept { m_x = x; }

  /// Set a player y position
  void set_y(double y) noexcept { m_y = y; }

  /// Turn the player left
  void turn_left() noexcept { m_direction_radians += m_turn_rate; }

  /// Turn the player right
  void turn_right() noexcept { m_direction_radians -= m_turn_rate; }

  /// Update the position of the player on the base of its speed and direction
  void update_player_position() noexcept
  {
    m_x += cos(m_direction_radians) * m_player_speed;
    m_y += sin(m_direction_radians) * m_player_speed;
  }

  /// Accelerate the player
  void accelerate() noexcept;

  /// Brake the player
  void brake() noexcept;

  /// Accelerate the player backward
  void acc_backward() noexcept;

private:
  /// The player's color, will change depending on food items
  color m_color;

  /// When a player shoots, 'm_is_shooting' is true for one tick.
  /// 'game' reads 'm_is_shooting' and if it is true,
  /// it (1) creates a projectile, (2) sets 'm_is_shooting' to false
  bool m_is_shooting{false};

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

  ///The backward acceleration of player
  double m_player_acc_backward;

  /// The size of the player
  double m_radius;

  /// The direction of player in radians
  double m_direction_radians;

  /// The rate at which the player turns
  double m_turn_rate;

  /// Player's health percentage, the player always start with max health at
  /// construction
  double m_health = 1.0;
};

/// Checks if two players are colliding
bool are_colliding(const player &p1, const player &p2) noexcept;

/// Get the blueness (from the color) of the player
int get_blueness(const player &p) noexcept;

/// Get the greenness (from the color) of the player
int get_greenness(const player &p) noexcept;

/// Get the redness (from the color) of the player
int get_redness(const player &p) noexcept;

/// Is a player blue?
bool is_blue(const player &p) noexcept;

/// Is a player green?
bool is_green(const player &p) noexcept;

/// Is a player red?
bool is_red(const player &p) noexcept;

/// Test the player class
void test_player();

#endif // PLAYER_H
