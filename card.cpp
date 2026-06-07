#include <raylib.h>
#include <cmath>
#include "card.hpp"

Card::Card(Texture2D& texture) {
    cardTexture = texture;
    position = Vector2{0.0f, 0.0f};
    hoverOffset = Vector2{0.0f, 0.0f};
    isHovered = false;
    cardRect = Rectangle{position.x, position.y, (float)cardTexture.width, (float)cardTexture.height};
    scale = 1.5f;
    outlineSize = 3.0f;
    currentRotation = 0.0f;
}

void Card::SetPosition(Vector2 newPos) {
    position = newPos;
    if (!isHovered)
        cardRect = {position.x, position.y, (float)cardTexture.width, (float)cardTexture.height};
}

void Card::SetHovered(bool hovered) {
    if (!hovered) hoverOffset = {0.0f, 0.0f};
    isHovered = hovered;
}

bool Card::IsHovered(Vector2 mousePos) {
    return CheckCollisionPointRec(mousePos, cardRect);
}

bool Card::IsClicked(Vector2 mousePos) {
    return IsHovered(mousePos) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool Card::IsDragged(Vector2 mousePos){
    return IsHovered(mousePos) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}

void Card::Draw() {
    if (isHovered) {
        DrawHovered();
    } else {
        cardRect = {position.x, position.y, (float)cardTexture.width, (float)cardTexture.height};
        DrawTextureV(cardTexture, position, WHITE);
    }
}

void Card::UpdateHovered() {
    Vector2 mousePos = GetMousePosition();
    float dt = IsDragged(mousePos) ? 0.050f : GetFrameTime();
    float speed = 8.0f;

    // resting center = natural center before any offset is applied
    Vector2 restCenter = {
        position.x + cardTexture.width  / 2.0f,
        position.y + cardTexture.height / 2.0f
    };

    // hover: subtle tilt (10% of displacement); drag: full follow so center chases mouse
    float bias = IsDragged(mousePos) ? 1.0f : 0.1f;
    Vector2 target = {
        (mousePos.x - restCenter.x) * bias,
        (mousePos.y - restCenter.y) * bias
    };

    hoverOffset.x += (target.x - hoverOffset.x) * speed * dt;
    hoverOffset.y += (target.y - hoverOffset.y) * speed * dt;

    float rotationSensitivity = IsDragged(mousePos) ? (float)GetFPS() / 360.0f : 0.2f; // 360 is jsut trial and error till it felt right
    currentRotation += GetMouseDelta().x * rotationSensitivity; // accumulates tilt based on mouse delta
    currentRotation += (0.0f - currentRotation) * speed * dt; // decays to 0.0f
}

void Card::DrawHovered() {
    UpdateHovered();

    float w = cardTexture.width  * scale;
    float h = cardTexture.height * scale;

    // visual center: natural card center + lerp offset
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
