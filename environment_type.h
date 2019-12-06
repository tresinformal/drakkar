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

std::string to_str(environment_type this_env_type);

void test_environment_type();

#endif // ENVIRONMENT_H
