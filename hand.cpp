#include <vector>
#include "hand.hpp"

Hand::Hand(int window_x, int window_y, float card_width, int max_hand_size) {
    cards = std::vector<Card>();
    this->card_width = card_width;
    this->max_hand_size = max_hand_size;
    hand_position = Vector2{static_cast<float>(window_x) / 2.0f, static_cast<float>(window_y) - 100.0f}; // hand centered at the bottom of the screen
    card_spacing = 40.0f;
    current_card_hovered = -1;
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

void Hand::Draw() {
    if(cards.empty()){return;}

    const float total_width = (cards.size() - 1) * card_spacing + card_width;
    const float start_x = hand_position.x - total_width / 2.0f;
    const Vector2 mousePos = GetMousePosition();

    // set card positions
    for (int i = 0; i < (int)cards.size(); ++i)
        cards[i].SetPosition(Vector2{start_x + i * card_spacing, hand_position.y});

    // check for hover
    current_card_hovered = -1;
    for (int i = (int)cards.size() - 1; i >= 0; --i) {
        if (cards[i].IsHovered(mousePos)) {
            current_card_hovered = i;
            break;
        }
    }

    // draw normal cards
    for (int i = 0; i < (int)cards.size(); ++i) {
        if (i != current_card_hovered)
            cards[i].Draw();
    }

    // draw hovered card last to draw it on top
    if (current_card_hovered != -1) {
        cards[current_card_hovered].DrawHovered();
    }

}