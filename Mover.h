#pragma once

#include "raylib.h"
#include "raymath.h"

class Mover {
private:
    Vector2 Position;
    Vector2 Velocity;
    Vector2 Size;
    Vector2 Acceleration;
    float AccelLimit;

public:

    Mover(Vector2 position);
    Mover() = default;
    ~Mover();

    void Update(); // Original movement method
    void UpdateMouseFollow(); // Alternate movement method..
    void UpdWVel(); // Movement with velocity.
    void UpdateRandomMovement(); // Random Movement.
    void Accelerate(Vector2 accel_rate);
    void LimitAccel(Vector2 limit);
    void CheckEdges();
    Vector2 Random2D();
    // Getters and setters
    void setPosition(Vector2 position);
    Vector2 getPosition();
    void setSize(Vector2 size);
    Vector2 getSize();
    Vector2 getAcceleration();
    Vector2 getVelocity();


};