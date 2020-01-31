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

const std::string to_str_food_type(food_type this_food_type);

void test_food_type();

#endif // FOOD_TYPE_H
