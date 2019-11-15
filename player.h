#ifndef PLAYER_H
#define PLAYER_H
#include "player_shape.h"

class player
{
public:
    player(const double x = 0.0,
           const double y = 0.0,
           const player_shape shape = player_shape::rocket,
           const double player_speed = 0,
           const double size = 100.0,
           const double direction = 0.0,
           const double turn_rate = 0.1);

    /// Get the X coordinat of the player
    double get_x() const noexcept { return m_x; }

    /// Get the Y coordinat of the player
    double get_y() const noexcept { return m_y; }

    /// Get the shape of the player
    player_shape get_shape() const noexcept { return m_shape; }

    ///Get the size of the player
    double get_size() const noexcept{ return m_size; }

    /// Get the speed of the player
    double get_speed() const noexcept { return m_player_speed; }

    /// Get the direction of player movement
    double get_direction() const noexcept{ return m_direction;}

    ///Get the player's health
    double get_health() const noexcept{ return m_health;}

    ///Turn the player left
    void turn_left() noexcept {m_direction += m_turn_rate;}

private:

    /// The X coordinat of the player
    double m_x;

    /// The Y coordinat of the player
    double m_y;

    ///The shape of the player
    player_shape m_shape;

    /// The speed of the player
    double m_player_speed;

    ///The size of the player
    double m_size;

    ///The direction of player
    double m_direction;

    ///The rate at which the player turns
    double m_turn_rate;

    ///Player's health percentage, the player always start with max health at construction
    double m_health = 1.0;
};

/// Test the player class
void test_player();


#endif // PLAYER_H
