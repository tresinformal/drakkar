#ifndef FOOD_H
#define FOOD_H

class food
{
public:
  food(const double x = 0.0, const double y = 0.0);

  double get_x() const noexcept { return f_x; }
  double get_y() const noexcept { return f_y; }

private:
  double f_x;
  double f_y;
};

void test_food();
#endif // FOOD_H
