#ifndef ENVIRONMENT_TYPE_H
#define ENVIRONMENT_TYPE_H

#include <string>

enum class environment_type
{
  empty,
  quiet,
  random,
  attractive,
  repellent,
  wormhole
};

void test_environment_type();
std::string to_str_env_type(environment_type this_environment_type);

#endif // ENVIRONMENT_H
