#include <vector>
#include "hand.hpp"

Hand::Hand(int window_x, int window_y, float card_width, int max_hand_size) {
    cards = std::vector<Card>();
    this->card_width = card_width;
    this->max_hand_size = max_hand_size;
    hand_position = Vector2{static_cast<float>(window_x) / 2.0f, static_cast<float>(window_y) - 200.0f}; // hand centered at the bottom of the screen
    card_spacing = 40.0f;
    lastHovered = -1;
}

void Hand::AddCard(const Card& card) {
    if (cards.size() < max_hand_size) {
        cards.push_back(card);
    }
}

void Hand::RemoveCard(int index) {
    int back = (int)cards.size() - 1;
    if (lastHovered == index) {
        cards[index].SetHovered(false);
        lastHovered = -1;
    } else if (lastHovered == back) {
        lastHovered = index;
    }
    cards[index] = std::move(cards.back());
    cards.pop_back();
}

void Hand::Clear() {
    cards.clear();
}

std::vector<Card>& Hand::GetCards() {
    return cards;
}

void Hand::Draw() {
    if(cards.empty()){return;}

    const float total_width = (cards.size() - 1) * card_spacing + card_width;
    const float start_x = hand_position.x - total_width / 2.0f;
    const Vector2 mousePos = GetMousePosition();

    for (int i = 0; i < (int)cards.size(); ++i)
        cards[i].SetPosition(Vector2{start_x + i * card_spacing, hand_position.y});

    int hovered = -1;
    for (int i = (int)cards.size() - 1; i >= 0; --i) {
        if (cards[i].IsHovered(mousePos)) {
            hovered = i;
            break;
        }
    }

    // if the hovered card changed, set previous to false 
    if (lastHovered != hovered) {
        if (lastHovered != -1) cards[lastHovered].SetHovered(false);
        if (hovered != -1)           cards[hovered].SetHovered(true);
        lastHovered = hovered;
    }

    // draw unhovered cards first, then draw hovered card
    for (int i = 0; i < (int)cards.size(); ++i)
        if (i != lastHovered) cards[i].Draw();

    if (lastHovered != -1)
        cards[lastHovered].Draw();

}