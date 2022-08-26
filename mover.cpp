#include "Mover.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

Mover::Mover(Vector2 position) {
    this->Position = position;
    this->Velocity = { 0, 0 };
    this->Acceleration = { 0, 0 };
    this->AccelLimit = 6.0f;
}

Mover::~Mover() {
    // UnMover stuff.
}

void Mover::Update() {
    // Simple movement.
    if (IsKeyDown(KEY_LEFT)){
        this->Velocity = { -6, 0 };
        this->Position = Vector2Add(this->Position, this->Velocity);
    }
    if (IsKeyDown(KEY_RIGHT)){
        this->Velocity = { 6, 0 };
        this->Position = Vector2Add(this->Position, this->Velocity);
    }
    if (IsKeyDown(KEY_UP)){
        this->Velocity = { 0, -6 };
        this->Position = Vector2Add(this->Position, this->Velocity);
    }
    if (IsKeyDown(KEY_DOWN)){
        this->Velocity = { 0, 6 };
        this->Position = Vector2Add(this->Position, this->Velocity);
    }
    this->CheckEdges();
}
void Mover::CheckEdges() {
    if (this->Position.x >= GetScreenWidth() - this->Size.x){
        this->Position.x = GetScreenWidth() - this->Size.x;
    }
    if (this->Position.x <= 0) {
        this->Position.x = 0 ;
    }
    if (this->Position.y >= GetScreenHeight() - this->Size.y) {
        this->Position.y = GetScreenHeight() - this->Size.y;
    }
    if (this->Position.y <= 0) {
        this->Position.y = 0 ;
    }
}
/**
 * @brief Trying to get velocity to work, moving it into it's own code for now.
 *
 */
void Mover::UpdWVel() {
    // Movement with acceleration applied.
    if (IsKeyDown(KEY_LEFT)){
        // Reset the Velocity and Acceleration for the y axis.
        this->Velocity.y = 0.0f;
        this->Acceleration.y = 0.0f;

        // Do acceleration.
        this->Accelerate({ -0.2f, 0.0f });

        // Limit the velocity to something under the speed of light.
        if (this->Velocity.x < -6) this->Velocity.x = -6;
        if (this->Velocity.x > -0) this->Velocity.x = -0;

        // Set the position.
        this->Position = Vector2Add(this->Position, this->Velocity);
        this->Acceleration = Vector2Multiply(this->Acceleration, { 0, 0 });

    }

    if (IsKeyDown(KEY_RIGHT)){
        this->Acceleration.y = 0.0f;
        this->Velocity.y = 0.0f;

        this->Accelerate({ 0.2f, 0.0f });

        if (this->Velocity.x > 6) this->Velocity.x = 6;
        if (this->Velocity.x < 0) this->Velocity.x = 0;

        this->Position = Vector2Add(this->Position, this->Velocity);
        this->Acceleration = Vector2Multiply(this->Acceleration, { 0, 0 });

    }
    if (IsKeyDown(KEY_UP)){
        this->Acceleration.x = 0.0f;
        this->Velocity.x = 0.0f;

        this->Accelerate({ 0.0f, -0.2f });

        if (this->Velocity.y < -6) this->Velocity.y = -6;
        if (this->Velocity.y > -0) this->Velocity.y = -0;

        this->Position = Vector2Add(this->Position, this->Velocity);
        this->Acceleration = Vector2Multiply(this->Acceleration, { 0, 0 });

    }
    if (IsKeyDown(KEY_DOWN)){
        this->Acceleration.x = 0.0f;
        this->Velocity.x = 0.0f;

        this->Accelerate({ 0.0f, 0.2f });

        if (this->Velocity.y > 6) this->Velocity.y = 6;
        if (this->Velocity.y < 0) this->Velocity.y = 0;

        this->Position = Vector2Add(this->Position, this->Velocity);
        this->Acceleration = Vector2Multiply(this->Acceleration, { 0, 0 });

    }
    this->CheckEdges();
}

void Mover::UpdateMouseFollow() {
    // Chase the mouse
    Vector2 MousePos = { (float)GetMouseX(), (float)GetMouseY() };

    Vector2 Dir = Vector2Subtract(MousePos, this->Position);
    Dir = Vector2Normalize(Dir);
    Dir = Vector2Multiply(Dir, { 0.5f, 0.5f });
    this->Acceleration = Dir;
    this->Velocity = Vector2Add(this->Velocity, this->Acceleration);
    this->Velocity = Vector2ClampValue(this->Velocity, -4.0f, 4.0f);
    this->Position = Vector2Add(this->Position, this->Velocity);
    this->CheckEdges();

}

void Mover::UpdateRandomMovement() {
    this->Acceleration = Vector2Multiply(
                            Vector2Normalize(
                                Vector2Add(
                                    this->Acceleration,
                                    Vector2Multiply(
                                        this->Random2D(),
                                        {-0.5f, 0.5f}
                                    )
                                )
                            ),
                            {(float)GetRandomValue(-2,2), (float)GetRandomValue(-2, 2)}
                        );
    this->Velocity = Vector2Add(this->Velocity, this->Acceleration);
    this->Velocity = Vector2ClampValue(this->Velocity, -4.0f, 4.0f);
    this->Position = Vector2Add(this->Position, this->Velocity);
    this->CheckEdges();
    this->Acceleration = Vector2Zero();

}

void Mover::LimitAccel(Vector2 limit) {
    // Limit the Velocity vector
}

Vector2 Mover::Random2D(){
    Vector2 randVector = { (float)GetRandomValue(0, 800), (float)GetRandomValue(0, 600)};
    return Vector2Normalize(randVector);
}

void Mover::Accelerate(Vector2 accel_rate){
    this->Velocity = Vector2Add(this->Velocity, accel_rate);

}

/**
 * @brief Helper Function to allow children classes to utilize this base class.
 * This function sets the position which children classes (maybe not?) will use.
 * @param position
 */
void Mover::setPosition(Vector2 position){
    this->Position = position;
}

/**
 * @brief Helper function to allow children classes to utilize this base class.
 * this function gets the position for children classes to use.
 * @return Vector2
 */
Vector2 Mover::getPosition(){
    return this->Position;
}

Vector2 Mover::getAcceleration(){
    return this->Acceleration;
}
Vector2 Mover::getVelocity(){
    return this->Velocity;
}

void Mover::setSize(Vector2 size) {
    this->Size = size;
}

Vector2 Mover::getSize(){
    return this->Size;
}