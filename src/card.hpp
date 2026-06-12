#pragma once
#include <raylib.h>

enum class CardState { Idle, Hovered, Dragged };

struct StateParams {
    float speed;
    float bias;
    float yOffset;
    float scale;
};

class Card
{
    public:
        Card(Texture2D& texture);

        void SetState(CardState newState);
        void SetPosition(Vector2 newPos);
        void SetParams(CardState state, StateParams params);
        bool IsHovered(Vector2 mousePos) const;
        bool IsClicked(Vector2 mousePos) const;
        bool IsReleased() const;
        Rectangle GetRect() const;
        void Draw();

    private:
        void UpdateOffset(float speed, float bias, float yOffset);
        void DrawSpecial(float scale);

        Texture2D cardTexture;
        Vector2 position;
        Vector2 hoverOffset;
        Rectangle cardRect;

        CardState state;
        float outlineSize;
        float currentRotation;

        StateParams hoveredParams;
        StateParams draggedParams;
};
