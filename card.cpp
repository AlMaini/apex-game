#include <raylib.h>
#include <raymath.h>
#include "card.hpp"

Card::Card(Texture2D& texture) {
    cardTexture = texture;
    position = {0.0f, 0.0f, 0.0f};
    hoverOffset = {0.0f, 0.0f, 0.0f};
    isHovered = false;

    float w = (float)cardTexture.width;
    float h = (float)cardTexture.height;
    Mesh mesh = GenMeshPlane(w, h, 1, 1);
    cardModel = LoadModelFromMesh(mesh);
    SetMaterialTexture(&cardModel.materials[0], MATERIAL_MAP_DIFFUSE, cardTexture);
}

void Card::SetHovered(bool hovered) {
    if (!hovered) hoverOffset = {0.0f, 0.0f, 0.0f};
    isHovered = hovered;
}

void Card::Draw() {
    if (isHovered) {
        DrawHovered();
    } else {
        DrawModelEx(cardModel, position, {1.0f, 0.0f, 0.0f}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
    }
}

void Card::DrawHovered() {
    Vector2 mousePos = GetMousePosition();
    float dt = GetFrameTime();
    float speed = 8.0f;

    float targetX = (mousePos.x - GetScreenWidth()  / 2.0f) * 0.03f;
    float targetZ = (mousePos.y - GetScreenHeight() / 2.0f) * 0.03f;

    hoverOffset.x += (targetX - hoverOffset.x) * speed * dt;
    hoverOffset.z += (targetZ - hoverOffset.z) * speed * dt;

    Vector3 drawPos = {
        position.x + hoverOffset.x,
        position.y + 40.0f,
        position.z + hoverOffset.z
    };

    DrawModelEx(cardModel, drawPos, {1.0f, 0.0f, 0.0f}, 0.0f, {1.0f, 1.0f, 1.0f}, YELLOW);
}

bool Card::IsHovered(Ray ray) {
    Matrix transform = MatrixTranslate(position.x, position.y, position.z);
    RayCollision col = GetRayCollisionMesh(ray, cardModel.meshes[0], transform);
    return col.hit;
}

bool Card::IsClicked(Ray ray) {
    return IsHovered(ray) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Card::SetPosition(Vector3 newPos) {
    position = newPos;
}
