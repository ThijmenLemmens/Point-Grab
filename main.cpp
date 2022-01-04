#include <iostream>
#include "random"
#include "raylib.h"

const int width = 800;
const int height = 500;

int x = 375;
int y = 400;
int size_player = 50;

int point_x = width / 2;
int point_y = height / 2;
int size_points = 15;

bool won = false;
bool debug = false;
int speed = 4;
int points = 0;

void controls() {
    if (IsKeyDown(KEY_F1)) {
        if (!debug) {
            debug = true;
        } else {
            debug = false;
        }
    }
    if (!won) {
        if (IsKeyDown(KEY_UP)) y -= speed;
        if (IsKeyDown(KEY_DOWN)) y += speed;
        if (IsKeyDown(KEY_RIGHT)) x += speed;
        if (IsKeyDown(KEY_LEFT)) x -= speed;
    }
    if (IsKeyDown(KEY_R)) {
        points = 0;
        won = false;
        x = 375;
        y = 400;
        point_x = width / 2;
        point_y = height / 2;
    }
}

void collision() {
    std::random_device random;
    std::mt19937 gen(random());
    std::uniform_int_distribution<> random_number_x(0, width);
    std::uniform_int_distribution<> random_number_y(0, height);

    if (x < point_x + size_points &&
        x + size_player > point_x &&
        y < point_y + size_points &&
        size_player + y > point_y) {
        points++;
        point_x = random_number_x(gen);
        point_y = random_number_y(gen);
    }
}

void point_control() {
    if (point_x < 10) {
        point_x += 10;
    }
    if (point_x > width - 10) {
        point_x -= 10;
    }
    if (point_y < 10) {
        point_y += 10;
    }
    if (point_y > height - 10) {
        point_y -= 10;
    }
}

void border_control() {
    if (x < 0) {
        x = width - 10;
    }
    if (x > width) {
        x = 0;
    }
    if (y < 0) {
       y = height;
    }
    if (y > height) {
        y = 0;
    }
}

void debug_menu() {
    if (debug) {
        DrawText(TextFormat("FrameTime: %03i", GetFrameTime()), 100, 10, 20, DARKGREEN);
        DrawFPS(10, 10);
        DrawText(TextFormat("X: %03i", x), 350, 10, 20, DARKGREEN);
        DrawText(TextFormat("Y: %03i", y), 450, 10, 20, DARKGREEN);
    }
}

void win() {
    if (points == 20) {
        DrawText("You have won!", 250, 200, 50, GREEN);
        DrawText("R for reset!", 270, 250, 50, GREEN);
        won = true;
    }
}

void game_loop() {
    while(!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Grab the green points!", 300, 150, 20, LIGHTGRAY);
        DrawText(TextFormat("Points: %03i", points), 350, 50, 20, LIGHTGRAY);
        DrawText(TextFormat("Debug: %03i", debug), 650, 20, 20, LIGHTGRAY);

        debug_menu();
        collision();
        controls();
        border_control();
        point_control();
        win();
        DrawRectangle(x, y, size_player,size_player, RED);
        DrawRectangle(point_x, point_y, size_points,size_points, GREEN);

        EndDrawing();
    }
}

int main() {

    InitWindow(width, height, "Window");
    InitAudioDevice();

    SetTargetFPS(60);

    game_loop();

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
