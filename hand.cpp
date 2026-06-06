#include <vector>
#include "hand.hpp"

Hand::Hand() {
    cards = std::vector<Card>();
}

void Hand::AddCard(const Card& card) {
    cards.push_back(card);
}

std::vector<Card>& Hand::GetCards() {
    return cards;
}

void Hand::Draw() {
    // Reset the position of the cards in the hand and draw them
    for (size_t i = 0; i < cards.size(); ++i) {
        cards[i].SetPosition(Vector2{100.0f + i * 150.0f, 600.0f});
        cards[i].Draw();
    }
}