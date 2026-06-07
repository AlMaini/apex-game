#include <raylib.h>
#include <cmath>
#include "card.hpp"

Card::Card(Texture2D& texture) {
    cardTexture = texture;
    position = Vector2{0.0f, 0.0f};
    hoverOffset = Vector2{0.0f, 0.0f};
    state = CardState::Idle;
    cardRect = Rectangle{position.x, position.y, (float)cardTexture.width, (float)cardTexture.height};
    scale = 1.5f;
    outlineSize = 3.0f;
    currentRotation = 0.0f;
}

void Card::SetPosition(Vector2 newPos) {
    position = newPos;
    if (state == CardState::Idle)
        cardRect = {position.x, position.y, (float)cardTexture.width, (float)cardTexture.height};
}

void Card::SetState(CardState newState) {
    if (newState == CardState::Idle) hoverOffset = {0.0f, 0.0f};
    state = newState;
}

bool Card::IsHovered(Vector2 mousePos) const {
    return CheckCollisionPointRec(mousePos, cardRect);
}

bool Card::IsClicked(Vector2 mousePos) const {
    return IsHovered(mousePos) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool Card::IsReleased() const {
    return state == CardState::Dragged && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}

Rectangle Card::GetRect() const {
    return cardRect;
}

void Card::Draw() {
    if (state == CardState::Dragged) {
        UpdateOffset(20.0f, 1.0f, 0.0f);
        DrawSpecial();
    } else if (state == CardState::Hovered) {
        UpdateOffset(8.0f, 0.1f, 25.0f);
        DrawSpecial();
    } else {
        cardRect = {position.x, position.y, (float)cardTexture.width, (float)cardTexture.height};
        DrawTextureV(cardTexture, position, WHITE);
    }
}

void Card::UpdateOffset(float speed, float bias, float yOffset) {
    Vector2 mousePos = GetMousePosition();
    float dt = GetFrameTime();

    Vector2 restCenter = {
        position.x + cardTexture.width  / 2.0f,
        position.y + cardTexture.height / 2.0f
    };

    Vector2 target = {
        (mousePos.x - restCenter.x) * bias,
        (mousePos.y - restCenter.y) * bias
    };

    hoverOffset.x += (target.x - hoverOffset.x) * speed * dt;
    hoverOffset.y += (target.y - hoverOffset.y - yOffset) * speed * dt;

    float rotationSensitivity = (state == CardState::Dragged)
        ? (float)GetFPS() / 360.0f
        : 0.2f;
    currentRotation += GetMouseDelta().x * rotationSensitivity;
    currentRotation += (0.0f - currentRotation) * speed * dt;
}

void Card::DrawSpecial() {
    float w = cardTexture.width  * scale;
    float h = cardTexture.height * scale;

    Vector2 pivot = {
        position.x + cardTexture.width  / 2.0f + hoverOffset.x,
        position.y + cardTexture.height / 2.0f + hoverOffset.y
    };

    cardRect = { pivot.x - w / 2.0f, pivot.y - h / 2.0f, w, h };

    Rectangle src     = { 0, 0, (float)cardTexture.width, (float)cardTexture.height };
    Rectangle cardDst = { pivot.x, pivot.y, w, h };
    Rectangle outline = { pivot.x, pivot.y, w + outlineSize * 2.0f, h + outlineSize * 2.0f };

    DrawRectanglePro(outline, { outline.width / 2.0f, outline.height / 2.0f }, currentRotation, YELLOW);
    DrawTexturePro(cardTexture, src, cardDst, { w / 2.0f, h / 2.0f }, currentRotation, WHITE);
}
