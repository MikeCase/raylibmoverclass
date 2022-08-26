#include "Mover.h"
#include "Player.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

/**
 * @brief Construct a new Player:: Player object
 *
 * @param position
 */
Player::Player(Vector2 position, Vector2 size){
    setPosition(position);
    setSize(size);
    this->Rect.x = getPosition().x + (48/2);
    this->Rect.y = getPosition().y + (48/2);
    this->Rect.width = size.x;
    this->Rect.height = size.y;
    this->updateStyle = UPDATE_REGULAR;
}

/**
 * @brief Destroy the Player:: Player object
 *
 */
Player::~Player(){}

void Player::Update(){

    if (GetMouseX() >= 788 or GetMouseX() <= 10 or GetMouseY() >= 588 or GetMouseY() <= 10){
        this->chooseUpdateStyle(UPDATE_RANDOM);
    } else {
        this->chooseUpdateStyle(UPDATE_MOUSE_FOLLOW);
    }
    // std::cout << GetMouseY() << std::endl;

    // Mover::Update();
    // Mover::UpdateMouseFollow();
    // Mover::UpdWVel();
    // Mover::UpdateRandomMovement();

    this->Rect.x = getPosition().x;
    this->Rect.y = getPosition().y;
    this->Shoot();
}

/**
 * @brief Display the Player
 *
 */
void Player::Display() {
    DrawRectangleRec(this->Rect, RAYWHITE);
    if (this->shooting) {
        DrawRectangle(getPosition().x+(this->Rect.width/2), getPosition().y-15, 2, 15, RED);
        this->shooting = false;
    }
}

void Player::Shoot(){
    if (IsKeyDown(KEY_SPACE) && !this->shooting) {
        this->shooting = true;
    }
}

Vector2 Player::getAcceleration() {
    return Mover::getAcceleration();
}

Vector2 Player::getVelocity() {
    return Mover::getVelocity();
}

void Player::chooseUpdateStyle(int updStyle){
    this->updateStyle = updStyle;

    switch (this->updateStyle)
    {
    case UPDATE_REGULAR:
        Mover::Update();
        break;
    case UPDATE_MOUSE_FOLLOW:
        Mover::UpdateMouseFollow();
        break;
    case UPDATE_W_ACCEL:
        Mover::UpdWVel();
        break;
    case UPDATE_RANDOM:
        Mover::UpdateRandomMovement();
        break;
    default:
        Mover::Update();
        break;
    }
}