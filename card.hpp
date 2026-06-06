#pragma once
#include <raylib.h>

class Card
{
    public:
        Card(Texture2D& texture, Vector2 pos); // Constructor
        void Draw();
        bool IsHovered(Vector2 mousePos);
        bool IsClicked(Vector2 mousePos);
        void SetPosition(Vector2 newPos);

    private:
        Texture2D cardTexture;
        Vector2 position;
};