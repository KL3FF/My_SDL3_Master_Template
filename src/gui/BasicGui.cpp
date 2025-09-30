#include <iostream>
#include "BasicGui.h"

// ===================== BasicGui =====================

// Konstruktor
BasicGui::BasicGui(float _x, float _y, float _depth) : x(_x), y(_y), depth(_depth)
{
    // optional: Initialisierung
}

// Destruktor
BasicGui::~BasicGui()
{
    std::cout << "BasicGui destroyed: " << uuid << "\n";
}

// Draw-Funktion
void BasicGui::Draw()
{
    std::cout << "BasicGui Draw at (" << x << ", " << y << ", " << depth << ")\n";
}

// Update-Funktion
void BasicGui::Update(double &ndt)
{
    std::cout << "BasicGui Update at (" << x << ", " << y << ", " << depth << ")\n";
}

// ===================== StartGui =====================

// Konstruktor
StartGui::StartGui(float _x, float _y, float _depth) : BasicGui(_x, _y, _depth)
{
}
StartGui::~StartGui()
{
    std::cout << "StartGui destroyed\n";
}

// Update-Funktion
void StartGui::Update(double &ndt)
{
    x += 50.0f * ndt; // Beispielbewegung
    // std::cout << "StartGui Update: x = " << x << "\n";
}

// Draw-Funktion
void StartGui::Draw()
{
    // std::cout << "Drawing StartGui at (" << x << ", " << y << ")\n";
}
