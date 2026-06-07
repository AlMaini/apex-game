#pragma once
#include <raylib.h>

class Card
{
    public:
        Card(Texture2D& texture);

        void SetHovered(bool hovered);
        void SetDragged(bool dragged);
        void SetPosition(Vector2 newPos);
        bool IsHovered(Vector2 mousePos);
        bool IsClicked(Vector2 mousePos);
        bool IsDragged(Vector2 mousePos);
        bool IsReleased();
        void Draw();

    private:
        void UpdateHovered();
        void UpdateDragged();
        void DrawSpecial();

        Texture2D cardTexture;
        Vector2 position;
        Vector2 hoverOffset;
        Rectangle cardRect;
        
        bool isHovered;
        bool isDragged;
        float scale;
        float outlineSize;
        float currentRotation;
};
