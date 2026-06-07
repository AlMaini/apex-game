#include <raylib.h>
#include "card.hpp"

Card::Card(Texture2D& texture) {
    cardTexture = texture;
    position = Vector2{0.0f, 0.0f};
    hoverOffset = Vector2{0.0f, 0.0f};
    isHovered = false;
    cardRect = Rectangle{position.x, position.y, (float)cardTexture.width, (float)cardTexture.height};
    scale = 1.5f;
}

void Card::SetHovered(bool hovered) {
    if (!hovered) hoverOffset = {0.0f, 0.0f};
    isHovered = hovered;
}

void Card::Draw() {
    if (isHovered) {
        DrawHovered();
    } else {
        cardRect = {position.x, position.y, (float)cardTexture.width, (float)cardTexture.height};
        DrawTextureV(cardTexture, position, WHITE);
    }
}

void Card::DrawHovered() {
    Vector2 mousePos = GetMousePosition();
    float dt = GetFrameTime();
    float speed = 8.0f;

    Vector2 cardCenter = {
        position.x + cardTexture.width  / 2.0f,
        position.y + cardTexture.height / 2.0f
    };
    Vector2 target = {
        (mousePos.x - cardCenter.x) * 0.1f,
        (mousePos.y - cardCenter.y) * 0.1f
    };
    hoverOffset.x += (target.x - hoverOffset.x) * speed * dt;
    hoverOffset.y += (target.y - hoverOffset.y) * speed * dt;

    float scale = 1.5f;
    Vector2 scaledPos = {
        (position.x + hoverOffset.x) - cardTexture.width  * (scale - 1.0f) / 2.0f,
        (position.y + hoverOffset.y) - cardTexture.height * (scale - 1.0f) / 2.0f
    };

    cardRect = {scaledPos.x, scaledPos.y, (float)cardTexture.width * scale, (float)cardTexture.height * scale};
    DrawTextureEx(cardTexture, scaledPos, 0.0f, scale, YELLOW);
}

bool Card::IsHovered(Vector2 mousePos) {
    return CheckCollisionPointRec(mousePos, cardRect);
}

bool Card::IsClicked(Vector2 mousePos) {
    return IsHovered(mousePos) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Card::SetPosition(Vector2 newPos) {
    position = newPos;
    if (!isHovered)
        cardRect = {position.x, position.y, (float)cardTexture.width, (float)cardTexture.height};
}
