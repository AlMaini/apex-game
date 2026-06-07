#pragma once

#include <vector>
#include <raylib.h>
#include "card.hpp"

class Hand {
    public:
        Hand(int window_x, int window_y, float card_width, int max_hand_size);
        void AddCard(const Card& card);
        void RemoveCard(int index);
        CardState GetActiveCardState();
        int GetActiveCardIndex();
        void Clear();
        void Draw();
        std::vector<Card>& GetCards();

    private:
        std::vector<Card> cards;
        int max_hand_size;
        Vector2 hand_position;
        float card_spacing;
        float card_width;
        int activeIndex;
        CardState activeState;
};