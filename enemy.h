#ifndef ENEMY_H
#define ENEMY_H


class enemy
{
public:
    enemy(const double x = 0.0,
          const double y = 0.0);

    /// Get the X coordinat of the player
    double get_x() const noexcept { return m_x; }

    /// Get the Y coordinat of the player
    double get_y() const noexcept { return m_y; }

private:

  /// The X coordinat of the enemy
  double m_x;

  /// The Y coordinat of the enemy
  double m_y;

};


void test_enemy ();
#endif // ENEMY_H
