#pragma once
#include <raylib.h>

class Card
{
    public:
        Card(Texture2D& texture);
        void Draw();
        void SetHovered(bool hovered);
        bool IsHovered(Vector2 mousePos);
        bool IsClicked(Vector2 mousePos);
        void SetPosition(Vector2 newPos);

    private:
        void DrawHovered();

        Texture2D cardTexture;
        Vector2 position;
        Vector2 hoverOffset;
        Rectangle cardRect;
        bool isHovered;
};
