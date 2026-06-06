#include <raylib.h>
#include "card.hpp"

// Constructor
Card::Card(Texture2D& texture) {
    cardTexture = texture;
    position = Vector2{0.0f, 0.0f};
}

void Card::Draw() {
    DrawTextureV(cardTexture, position, WHITE);
}

bool Card::IsHovered(Vector2 mousePos) {
    // Check if mouse position is within the card's rectanble but slighlty smaller to account for the hover effect
    return CheckCollisionPointRec(mousePos, {position.x * 1.05f, position.y *1.05f, (float)cardTexture.width * 0.95f, (float)cardTexture.height * 0.95f});
    
}

void Card::DrawHovered() {
    float scale = 1.5f;
    Vector2 scaledPos = {
        position.x - cardTexture.width  * (scale - 1.0f) / 2.0f,
        position.y - cardTexture.height * (scale - 1.0f) / 2.0f
    };
    DrawTextureEx(cardTexture, scaledPos, 0.0f, scale, GRAY);
}

bool Card::IsClicked(Vector2 mousePos) {
    return IsHovered(mousePos) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Card::SetPosition(Vector2 newPos) {
    position = newPos;
}