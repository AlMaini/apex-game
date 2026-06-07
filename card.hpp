#pragma once
#include <raylib.h>

class Card
{
    public:
        Card(Texture2D& texture);

        void SetHovered(bool hovered);
        void SetPosition(Vector2 newPos);
        bool IsHovered(Vector2 mousePos);
        bool IsClicked(Vector2 mousePos);
        bool IsDragged(Vector2 mousePos);

        void Draw();

    private:
        void DrawHovered();
        

        Texture2D cardTexture;
        Vector2 position;
        Vector2 hoverOffset;
        Rectangle cardRect;
        
        bool isHovered;
        float scale;
        float outlineSize;
};
