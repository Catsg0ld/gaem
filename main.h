#ifndef MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#define PLAYER_TEXTURE_FWD "assets/you_fwd.png"
#define PLAYER_TEXTURE_FWD_1 "assets/you_fwd_1.png"
#define PLAYER_TEXTURE_FWD_2 "assets/you_fwd_2.png"
#define PLAYER_TEXTURE_LEFT "assets/you_left.png"
#define PLAYER_TEXTURE_LEFT_1 "assets/you_left_1.png"
#define PLAYER_TEXTURE_LEFT_2 "assets/you_left_2.png"
#define PLAYER_TEXTURE_RIGHT "assets/you_right.png"
#define PLAYER_TEXTURE_RIGHT_1 "assets/you_right_1.png"
#define PLAYER_TEXTURE_RIGHT_2 "assets/you_right_2.png"
#define PLAYER_TEXTURE_BKWD "assets/you_bkwd.png"
#define PLAYER_TEXTURE_BKWD_1 "assets/you_bkwd_1.png"
#define PLAYER_TEXTURE_BKWD_2 "assets/you_bkwd_2.png"

#define PLAYER_HEIGHT 80
#define PLAYER_WIDTH 80
#define PLAYER_MOVEMENT_SPEED 1

#define W_HEIGHT 800
#define W_WIDTH 800
#define W_TITLE "gaem,"
#define BG_COLOR (Color){0x15, 0x10, 0x10, 0xFF}

#define USE_Y 0
#define USE_X 1

#define TARGET_FPS 60

typedef enum Direction {
    FORWARD,
    LEFT,
    RIGHT,
    BACKWARD,
} Direction;

typedef struct Player {
    Texture2D player_textures[12];
    Vector2 position;
    Color color;
    int animation_frame;
    Direction direction;
} Player;

Player create_player(Vector2 position) {
    return (Player) {
        .player_textures = {
            LoadTexture(PLAYER_TEXTURE_FWD),
            LoadTexture(PLAYER_TEXTURE_FWD_1),
            LoadTexture(PLAYER_TEXTURE_FWD_2),
            LoadTexture(PLAYER_TEXTURE_LEFT),
            LoadTexture(PLAYER_TEXTURE_LEFT_1),
            LoadTexture(PLAYER_TEXTURE_LEFT_2),
            LoadTexture(PLAYER_TEXTURE_RIGHT),
            LoadTexture(PLAYER_TEXTURE_RIGHT_1),
            LoadTexture(PLAYER_TEXTURE_RIGHT_2),
            LoadTexture(PLAYER_TEXTURE_BKWD),
            LoadTexture(PLAYER_TEXTURE_BKWD_1),
            LoadTexture(PLAYER_TEXTURE_BKWD_2),
        },
        .position = position,
        .color = WHITE,
        .animation_frame = 0,
        .direction = FORWARD,
    };
}

void draw_player(Player* player) {

    int texture_index = player->direction * 3 + player->animation_frame;

    #ifdef DEBUG
    printf("[animation data] af:%d d:%d idx:%d\n", player->animation_frame, player->direction, texture_index);
    #endif // DEBUG
    DrawTextureV(player->player_textures[texture_index], player->position, player->color);
}

void move_player_abs(Player* player, Vector2 new_pos) {
    player->position = new_pos;
}

void move_player_rel(Player* player, int amount, int x_or_y) {
    if (x_or_y == USE_X) {
        player->position.x += amount * 80;
        if (player->position.x > W_WIDTH - PLAYER_WIDTH) {
            player->position.x = W_WIDTH - PLAYER_WIDTH;
        } else if (player->position.x < 0) {
            player->position.x = 0;
        }
    } else if (x_or_y == USE_Y) {
        player->position.y += amount * 80;
        if (player->position.y > W_HEIGHT - PLAYER_HEIGHT) {
            player->position.y = W_HEIGHT - PLAYER_HEIGHT;
        } else if (player->position.y < 0) {
            player->position.y = 0;
        }
    } else {
        fprintf(stderr, "%s\n", "[ERROR] Incorrect param in move_player_rel");
        exit(1);
    }
    #ifdef DEBUG
    printf("[movement data] Δ:%d Δf:%f x/y:%d\n", amount, amount * 80.0f, x_or_y);
    #endif // DEBUG
}

void draw_grid(Color color) {
    for (int y = 1; y < W_WIDTH / 80; y++) {
        for (int x = 1; x < W_HEIGHT / 80; x++) {
            DrawLineV(
                (Vector2){0, y*80}, 
                (Vector2){W_WIDTH, y*80},
                color
            );
        }
        DrawLineV(
            (Vector2){y*80, 0}, 
            (Vector2){y*80, W_HEIGHT},
            color
        );
    }
}

bool movement_key_pressed() {
    return IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D); 
}

#endif // MAIN_H