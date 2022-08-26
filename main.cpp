#include "raylib.h"
#include "raymath.h"
#include "Player.h"
#include <iostream>

/**
 * @brief This demonstrates how to build an entity from a mover baseclass.
 * In this case the player inherits the Mover baseclass. This allows the player entity
 * to have movement.
 *
 * The Mover baseclass doesn't have a whole lot of movement capabilities yet but I plan to add
 * to that.
 *
 * Right now you have 4 different movement styles.
 * 1. Top Down, from screen edge to screen edge.
 * 2. Top Down with acceleration.
 * 3. Random movement around the screen, reminds me of a pesky fly.
 * 4. Chasing the mouse pointer.
 *
 * I plan to add movement for basic 2d platformer
 * as well as a jumper style of movement.
 * I also would like to implement the flappybird movement style as well
 *
 * @return int
 */
int main() {

    InitWindow(800, 600, "Mover Class");

    Player p({400, 300}, {48,48});

    SetTargetFPS(60);

    while(!WindowShouldClose()){
        p.Update();

        BeginDrawing();

        ClearBackground(DARKGRAY);
        DrawFPS(10,40);
        // std::cout << p.getVelocity().y << std::endl;
        DrawText(TextFormat("Acceleration: %.2f", p.getAcceleration().y), 10, 60, 15, RAYWHITE);
        DrawText(TextFormat("Velocity: %.2f", p.getVelocity().y), 10, 80, 15, RAYWHITE);
        p.Display();

        EndDrawing();

    }
    CloseWindow();
    return 0;
}