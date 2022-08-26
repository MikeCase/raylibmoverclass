#pragma once

#include "Mover.h"
#include "raylib.h"
#include "raymath.h"

#define UPDATE_REGULAR 1
#define UPDATE_W_ACCEL 2
#define UPDATE_MOUSE_FOLLOW 3
#define UPDATE_RANDOM 4


class Player: private Mover {
private:

    bool shooting;
    Rectangle Rect;
    int updateStyle;


public:

    Player(Vector2 position, Vector2 size);
    Player() = default;
    ~Player();

    void Display();
    void Shoot();
    void Update();
    void chooseUpdateStyle(int updStyle);
    Vector2 getAcceleration();
    Vector2 getVelocity();

};