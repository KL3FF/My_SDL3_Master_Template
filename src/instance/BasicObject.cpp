#include <iostream>
#include "BasicObject.h"

// ===================== BasicObject =====================

// Konstruktor
BasicObject::BasicObject(float _x, float _y, float _depth) : x(_x), y(_y), depth(_depth)
{
    // optional: Initialisierung
}

// Destruktor
BasicObject::~BasicObject()
{
    std::cout << "BasicObject destroyed: " << uuid << "\n";
}

// Draw-Funktion
void BasicObject::Draw()
{
    std::cout << "BasicObject Draw at (" << x << ", " << y << ", " << depth << ")\n";
}

// Update-Funktion
void BasicObject::Update(double &ndt)
{
    std::cout << "BasicObject Update at (" << x << ", " << y << ", " << depth << ")\n";
}

// ===================== Player =====================

// Konstruktor
Player::Player(float _x, float _y, float _depth) : BasicObject(_x, _y, _depth)
{
}
Player::~Player()
{
    std::cout << "Player destroyed\n";
}

// Update-Funktion
void Player::Update(double &ndt)
{
    x += 50.0f * ndt; // Beispielbewegung
    // std::cout << "Player Update: x = " << x << "\n";
}

// Draw-Funktion
void Player::Draw()
{
    // std::cout << "Drawing Player at (" << x << ", " << y << ")\n";
}
