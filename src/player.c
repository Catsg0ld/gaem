// Made by (c) Catsgold

#include <player.h>
#include <stdlib.h>
#if DEBUG == 1
#include <stdio.h>
#endif

void Player_LoadAnimation(struct Player* player,
                          const char* paths[PLAYER_ANIMATION_LENGTH]) {
  if (!player) {
    return;
  }
  for (int i = 0; i < PLAYER_ANIMATION_LENGTH; ++i) {
    player->animation[i] = LoadTexture(paths[i]);
#if DEBUG == 1
    printf("Loaded animation frame: %s\n", paths[i]);
#endif
  }
}

void Player_UnloadAnimation(struct Player* player) {
  if (!player) {
    return;
  }
  for (int i = 0; i < PLAYER_ANIMATION_LENGTH; ++i) {
    UnloadTexture(player->animation[i]);
#if DEBUG == 1
    printf("Unloaded animation frame %d\n", i);
#endif
  }
}

#define CLAMP(v, lo, hi) (v + (lo - v) * (v < lo) + (hi - v) * (v > hi))

void Player_Move(struct Player* player, const Vector2 dir) {
  player->transform.position.x += dir.x * PLAYER_SIZE;
  player->transform.position.y += dir.y * PLAYER_SIZE;

  player->transform.position.x =
      CLAMP(player->transform.position.x, 0.0f, WINDOW_WIDTH - PLAYER_SIZE);
  player->transform.position.y =
      CLAMP(player->transform.position.y, 0.0f, WINDOW_HEIGHT - PLAYER_SIZE);
};

#undef CLAMP
