#pragma once
#include <raylib.h>

class Card
{
    public:
        Card(Texture2D& texture); // Constructor
        void Draw();
        void DrawHovered();
        bool IsHovered(Vector2 mousePos);
        bool IsClicked(Vector2 mousePos);
        void SetPosition(Vector2 newPos);

    private:
        Texture2D cardTexture;
        Vector2 position;
        Vector2 hoverOffset; // Offset for the hover effect
        Rectangle cardRect;
};