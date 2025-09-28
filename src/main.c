// Made by (c) lenanya
// Refactored by (c) Catsgold

#include <config.h>
#include <math.h>
#include <player.h>
#include <raylib.h>

void GenGridTexture(RenderTexture2D* gridTexture) {
  *gridTexture = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
  BeginTextureMode(*gridTexture);
  ClearBackground(BLANK);

  for (int i = 0; i < WINDOW_HEIGHT / 80; i++)
      DrawLine(0, i * 80, WINDOW_WIDTH, i * 80, GRAY);
  for (int i = 0; i < WINDOW_WIDTH / 80; i++)
      DrawLine(i * 80, 0, i * 80, WINDOW_HEIGHT, GRAY);

  EndTextureMode();
}

int main(void) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  SetTargetFPS(TARGET_FPS);

  Player_t player;
  
  RenderTexture2D gridTexture; 
  GenGridTexture(&gridTexture);

  const char* animPaths[PLAYER_ANIMATION_LENGTH] = {
      "assets/you_fwd.png",    // Front 0
      "assets/you_fwd_1.png",  // Front 1
      "assets/you_fwd_2.png",  // Front 2

      "assets/you_left.png",    // Left 0
      "assets/you_left_1.png",  // Left 1
      "assets/you_left_2.png",  // Left 2

      "assets/you_right.png",    // Right 0
      "assets/you_right_1.png",  // Right 1
      "assets/you_right_2.png",  // Right 2

      "assets/you_bkwd.png",    // Back 0
      "assets/you_bkwd_1.png",  // Back 1
      "assets/you_bkwd_2.png"   // Back 2
  };

  Player_LoadAnimation(&player, animPaths);

  int dir = 0, anim = 0;
  Vector2 deltaMove;
  while (!WindowShouldClose()) {
    static double lastTime = 0;

    // TODO: brush up this chunk, it looks ugly
    if (IsKeyDown(KEY_W)) {
      deltaMove.y = -1, dir = 3;
    }
    if (IsKeyDown(KEY_S)) {
      deltaMove.y = 1, dir = 0;
    }
    if (IsKeyDown(KEY_A)) {
      deltaMove.x = -1, dir = 1;
    }
    if (IsKeyDown(KEY_D)) {
      deltaMove.x = 1, dir = 2;
    }

    double now = GetTime();
    if (now - lastTime > 0.5) {
      anim = (anim + 1) % 3;

      Player_Move(&player, deltaMove);
      deltaMove.x = 0, deltaMove.y = 0;
      lastTime = now;
    }

    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);

    DrawTexture(gridTexture.texture, 0, 0, WHITE); 
    DrawTextureV(player.animation[dir * 3 + anim], player.transform.position,
                 WHITE);

    EndDrawing();
  }

  Player_UnloadAnimation(&player);
  UnloadRenderTexture(gridTexture);
  CloseWindow();
}
