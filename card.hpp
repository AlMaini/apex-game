#pragma once
#include <raylib.h>

class Card
{
    public:
        Card(Texture2D& texture);
        void Draw();
        void SetHovered(bool hovered);
        bool IsHovered(Ray ray);
        bool IsClicked(Ray ray);
        void SetPosition(Vector3 newPos);

    private:
        void DrawHovered();

        Texture2D cardTexture;
        Model cardModel;
        Vector3 position;
        Vector3 hoverOffset;
        bool isHovered;
};
