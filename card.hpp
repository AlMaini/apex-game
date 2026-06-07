#pragma once
#include <raylib.h>

enum class CardState { Idle, Hovered, Dragged };

class Card
{
    public:
        Card(Texture2D& texture);

        void SetState(CardState newState);
        void SetPosition(Vector2 newPos);
        bool IsHovered(Vector2 mousePos) const;
        bool IsClicked(Vector2 mousePos) const;
        bool IsReleased() const;
        Rectangle GetRect() const;
        void Draw();

    private:
        void UpdateOffset(float speed, float bias, float yOffset);
        void DrawSpecial();

        Texture2D cardTexture;
        Vector2 position;
        Vector2 hoverOffset;
        Rectangle cardRect;

        CardState state;
        float scale;
        float outlineSize;
        float currentRotation;
};
