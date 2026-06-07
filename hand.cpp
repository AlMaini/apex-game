#include <vector>
#include "hand.hpp"

Hand::Hand(int window_x, int window_y, float card_width, int max_hand_size) {
    cards = std::vector<Card>();
    this->card_width = card_width;
    this->max_hand_size = max_hand_size;
    hand_position = {static_cast<float>(window_x) / 2.0f, 0.0f, 0.0f};
    card_spacing = 40.0f;
    lastHovered = -1;
}

void Hand::AddCard(const Card& card) {
    if (cards.size() < max_hand_size) {
        cards.push_back(card);
    }
}

void Hand::RemoveCard(size_t index) {
    if (index < cards.size()) {
        cards.erase(cards.begin() + index);
    }
}

void Hand::Clear() {
    cards.clear();
}

std::vector<Card>& Hand::GetCards() {
    return cards;
}

void Hand::Draw(Camera3D camera) {
    if (cards.empty()) return;

    const float total_width = (cards.size() - 1) * card_spacing + card_width;
    const float start_x = hand_position.x - total_width / 2.0f;
    const Vector2 mousePos = GetMousePosition();
    const Ray ray = GetScreenToWorldRay(mousePos, camera);

    for (int i = 0; i < (int)cards.size(); ++i)
        cards[i].SetPosition({start_x + i * card_spacing, hand_position.y, hand_position.z});

    int hovered = -1;
    for (int i = (int)cards.size() - 1; i >= 0; --i) {
        if (cards[i].IsHovered(ray)) {
            hovered = i;
            break;
        }
    }

    if (lastHovered != hovered) {
        if (lastHovered != -1) cards[lastHovered].SetHovered(false);
        if (hovered != -1)     cards[hovered].SetHovered(true);
        lastHovered = hovered;
    }

    BeginMode3D(camera);

    // draw unhovered cards first, then hovered card on top
    for (int i = 0; i < (int)cards.size(); ++i)
        if (i != lastHovered) cards[i].Draw();

    if (lastHovered != -1)
        cards[lastHovered].Draw();

    EndMode3D();
}
