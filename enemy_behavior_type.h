#ifndef ENEMY_BEHAVIOR_TYPE_H
#define ENEMY_BEHAVIOR_TYPE_H

#include <string>

enum class enemy_behavior_type
{
  gezellig,
  shy
};

/// Test the enemy_behavior_type
void test_enemy_behavior_type();

/// Implement stream operator
std::stringstream& operator << (std::stringstream &out, const enemy_behavior_type &enemy_type);

#endif // ENEMY_BEHAVIOR_TYPE_H
