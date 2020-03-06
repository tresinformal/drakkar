#ifndef PROJECTILE_TYPE_H
#define PROJECTILE_TYPE_H
#include <iosfwd>

enum class projectile_type

{
  rocket,
  cat
};

std::ostream &operator<<(std::ostream &os, const projectile_type t);

const std::string to_str_projectile_type(projectile_type this_projectile_type);

void test_projectile_type();

#endif // PROJECTILE_TYPE_H
