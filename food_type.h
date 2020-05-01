#ifndef FOOD_TYPE_H
#define FOOD_TYPE_H
#include <iosfwd>

enum class food_type
{
  rocket,
  laser,
  poison,
  neutral,
  potion_of_camouflage
};

std::ostream &operator<<(std::ostream &os, const food_type t);

std::string to_str(const food_type this_food_type) noexcept;

void test_food_type();

#endif // FOOD_TYPE_H
