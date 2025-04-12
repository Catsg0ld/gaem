//#define DEBUG
#include "main.h"

int main(void) {
    InitWindow(W_WIDTH, W_HEIGHT, W_TITLE);

    Vector2 player_start_pos= {0,0};

    Player player = create_player(player_start_pos);

    SetTargetFPS(TARGET_FPS);

    int frame = 0;

    bool did_move = false;

    while (!WindowShouldClose()) {
        #ifdef DEBUG
        double beforetotal = GetTime();
        #endif //DEBUG
        BeginDrawing();
        ClearBackground(BG_COLOR);
        
        #ifdef DEBUG
        double beforegrid = GetTime();
        #endif //DEBUG

        draw_grid(GRAY);

        #ifdef DEBUG
        double aftergrid = GetTime();
        printf("[performance data] grid:%lfms\n", (aftergrid-beforegrid)*1000);
        printf("[frame data] f:%d ftm:%d\n", frame, abs(frame - 60));
        #endif // DEBUG

        if (frame % 10 == 0) {
            player.animation_frame = (player.animation_frame + 1) % 3; 
        }

        if (frame == 0 && did_move) {
            #ifdef DEBUG
            printf("[movement data] d:%d s:%d\n", player.direction, PLAYER_MOVEMENT_SPEED);
            #endif // DEBUG

            switch (player.direction) {
                case LEFT:
                    move_player_rel(&player, -PLAYER_MOVEMENT_SPEED, USE_X);
                    break;
                case RIGHT:
                    move_player_rel(&player, PLAYER_MOVEMENT_SPEED, USE_X);
                    break;
                case BACKWARD:
                    move_player_rel(&player, -PLAYER_MOVEMENT_SPEED, USE_Y);
                    break;
                case FORWARD:
                    move_player_rel(&player, PLAYER_MOVEMENT_SPEED, USE_Y);
                    break;
                default:
                    fprintf(stderr, "[ERROR] player.direction was %d\n", player.direction);
                    exit(1);
            }
            did_move = false;
        }

        if (movement_key_pressed()) {
            did_move = true;
            if (IsKeyDown(KEY_A)) {
                #ifdef DEBUG
                printf("[input data] %s\n", "KEY_A");
                #endif //DEBUG

                player.direction = LEFT;
            }
            if (IsKeyDown(KEY_D)) {
                #ifdef DEBUG
                printf("[input data] %s\n", "KEY_D");
                #endif //DEBUG

                player.direction = RIGHT;
            }
            if (IsKeyDown(KEY_W)) {
                #ifdef DEBUG
                printf("[input data] %s\n", "KEY_W");
                #endif //DEBUG

                player.direction = BACKWARD;
            }
            if (IsKeyDown(KEY_S)) {
                #ifdef DEBUG
                printf("[input data] %s\n", "KEY_S");
                #endif //DEBUG

                player.direction = FORWARD;
            }
        }

        #ifdef DEBUG
        double beforeplayer = GetTime();
        #endif //DEBUG

        draw_player(&player);

        #ifdef DEBUG
        double afterplayer = GetTime();
        printf("[performance data] player:%lfms\n", (afterplayer-beforeplayer)*1000);
        #endif //DEBUG
        

        frame = (frame + 1) % 60;
        EndDrawing();
        #ifdef DEBUG
        double aftertotal = GetTime();
        printf("[performance data] frame:%lfms\n", (aftertotal-beforetotal)*1000);
        #endif //DEBUG
    }

    return 0;
}