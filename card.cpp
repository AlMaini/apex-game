#include <raylib.h>
#include "card.hpp"

// Constructor
Card::Card(Texture2D& texture, Vector2 pos) {
    cardTexture = texture;
    position = pos;
}

void Card::Draw() {
    Vector2 mousePos = GetMousePosition();
    if (IsHovered(mousePos)) {
        float scale = 1.3f;
        Vector2 scaledPos = {
            position.x - cardTexture.width  * (scale - 1.0f) / 2.0f,
            position.y - cardTexture.height * (scale - 1.0f) / 2.0f
        };
        DrawTextureEx(cardTexture, scaledPos, 0.0f, scale, GRAY);
    } 
    else {
        DrawTextureV(cardTexture, position, WHITE);
    }
}

bool Card::IsHovered(Vector2 mousePos) {
    return CheckCollisionPointRec(mousePos, {position.x, position.y, (float)cardTexture.width, (float)cardTexture.height});
    
}

bool Card::IsClicked(Vector2 mousePos) {
    return IsHovered(mousePos) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Card::SetPosition(Vector2 newPos) {
    position = newPos;
}