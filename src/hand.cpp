#include <vector>
#include "hand.hpp"

Hand::Hand(int window_x, int window_y, float card_width, int max_hand_size) {
    cards = std::vector<Card>();
    this->card_width = card_width;
    this->max_hand_size = max_hand_size;

    hand_position = Vector2{
        static_cast<float>(window_x) / 2.0f,
        static_cast<float>(window_y) - 200.0f
    };

    card_spacing = (2.0f/3.0f) * card_width;
    activeIndex = -1;
    activeState = CardState::Idle;
}

void Hand::AddCard(const Card& card) {
    if (cards.size() < max_hand_size) {
        cards.push_back(card);
    }
}

void Hand::RemoveCard(int index) {
    int back = (int)cards.size() - 1;

    if (activeIndex == index) {
        cards[index].SetState(CardState::Idle);
        activeIndex = -1;
        activeState = CardState::Idle;
    } 
    else if (activeIndex == back) {
        activeIndex = index;
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

CardState Hand::GetActiveCardState(){
    return activeState;
}

int Hand::GetActiveCardIndex(){
    return activeIndex;
}

void Hand::Draw() {
    if (cards.empty()) return;

    const float total_width = (cards.size() - 1) * card_spacing + card_width;
    const float start_x = hand_position.x - total_width / 2.0f;
    const Vector2 mousePos = GetMousePosition();

    // place cards one by one in a line
    for (int i = 0; i < (int)cards.size(); ++i)
        cards[i].SetPosition({start_x + i * card_spacing, hand_position.y});

    // Detect active card: sticky drag takes priority, then right-to-left hover scan
    int newIndex = -1;
    CardState newState = CardState::Idle;

    // Is the active card still being dragged?
    if (activeState == CardState::Dragged && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        newIndex = activeIndex;
        newState = CardState::Dragged;
    }
    // Scan the deck to see what is being hovered or dragged from right to left
    else {
        for (int i = (int)cards.size() - 1; i >= 0; --i) {
            if (cards[i].IsHovered(mousePos)) {
                newIndex = i;
                newState = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? CardState::Dragged : CardState::Hovered;
                break;
            }
        }
    }

    // update what is active if it's changed
    if (activeIndex != newIndex || activeState != newState) {
        if (activeIndex != -1) cards[activeIndex].SetState(CardState::Idle);
        if (newIndex   != -1)  cards[newIndex].SetState(newState);
        activeIndex = newIndex;
        activeState = newState;
    }

    // Draw idle cards first, active card on top
    for (int i = 0; i < (int)cards.size(); ++i)
        if (i != activeIndex) cards[i].Draw();
    if (activeIndex != -1) cards[activeIndex].Draw();
}
