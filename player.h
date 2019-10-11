#ifndef PLAYER_H
#define PLAYER_H


class player
{
public:
  player(const double x, const double y);

  /// Get the X coordinat of the player
  double get_x() const noexcept { return m_x; }

  /// Get the Y coordinat of the player
  double get_y() const noexcept { return m_y; }

private:

  /// The X coordinat of the player
  double m_x;

  /// The Y coordinat of the player
  double m_y;
};

/// Test the player class
void test_player();


#endif // PLAYER_H
