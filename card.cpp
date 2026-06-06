#include <raylib.h>
#include "card.hpp"

// Constructor
Card::Card(Texture2D& texture) {
    cardTexture = texture;
    position = Vector2{0.0f, 0.0f};
    hoverOffset = Vector2{0.0f, 0.0f};
    cardRect = Rectangle{position.x, position.y, (float)cardTexture.width, (float)cardTexture.height};
}

void Card::Draw() {
    hoverOffset = {0.0f, 0.0f};
    DrawTextureV(cardTexture, position, WHITE);
}

bool Card::IsHovered(Vector2 mousePos) {
    // Check if mouse position is within the card's rectanble but slighlty smaller to account for the hover effect
    return CheckCollisionPointRec(mousePos, cardRect);
    
}

void Card::DrawHovered() {
    Vector2 mousePos = GetMousePosition();
    float dt = GetFrameTime();
    float speed = 8.0f;

    hoverOffset.x = (mousePos.x - hoverOffset.x) * speed * dt;
    hoverOffset.y = (mousePos.y - hoverOffset.y) * speed * dt;

    float scale = 1.5f;
    Vector2 scaledPos = {
        (position.x + hoverOffset.x) - cardTexture.width  * (scale - 1.0f) / 2.0f,
        (position.y + hoverOffset.y) - cardTexture.height * (scale - 1.0f) / 2.0f
    };

    scaledPos.y -= 40.f;

    DrawTextureEx(cardTexture, scaledPos, 0.0f, scale, GRAY);
}

bool Card::IsClicked(Vector2 mousePos) {
    return IsHovered(mousePos) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Card::SetPosition(Vector2 newPos) {
    position = newPos;
    cardRect = {position.x, position.y, (float)cardTexture.width, (float)cardTexture.height};
}