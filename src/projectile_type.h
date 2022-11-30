#ifndef PROJECTILE_TYPE_H
#define PROJECTILE_TYPE_H
#include <iosfwd>
#include<string>

enum class projectile_type
{
  rocket,
  cat,
  stun_rocket
};

std::ostream &operator<<(std::ostream &os, const projectile_type t);

std::string to_str(const projectile_type this_projectile_type) noexcept;

void test_projectile_type();

#endif // PROJECTILE_TYPE_H
