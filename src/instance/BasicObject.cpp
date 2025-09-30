#include <iostream>
#include "BasicObject.h"

// ===================== BasicObject =====================

// Konstruktor
BasicObject::BasicObject(float startX, float startY) : x(startX), y(startY)
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
    std::cout << "BasicObject Draw at (" << x << ", " << y << ")\n";
}

// Update-Funktion
void BasicObject::Update(double &ndt)
{
    // Default: tut nichts
}

// ===================== Player =====================

// Konstruktor
Player::Player(float startX, float startY)
    : BasicObject(startX, startY)
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
    std::cout << "Player Update: x = " << x << "\n";
}

// Draw-Funktion
void Player::Draw()
{
    std::cout << "Drawing Player at (" << x << ", " << y << ")\n";
}
