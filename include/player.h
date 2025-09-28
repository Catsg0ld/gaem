// Made by (c) Catsgold

#ifndef PLAYER_H
#define PLAYER_H

#include <config.h>
#include <raylib.h>

struct Player {
  struct Transform2D {
    Vector2 position;
  } transform;
  Texture2D animation[PLAYER_ANIMATION_LENGTH];
};

typedef struct Player Player_t;

void Player_LoadAnimation(struct Player* player,
                          const char* paths[PLAYER_ANIMATION_LENGTH]);
void Player_UnloadAnimation(struct Player* player);
void Player_Move(struct Player* player, const Vector2 dir);

#endif  // PLAYER_H
