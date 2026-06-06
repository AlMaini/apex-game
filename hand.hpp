#pragma once

#include <vector>
#include "card.hpp"

class Hand {
    public:
        Hand();
        void AddCard(const Card& card);
        void Draw();
        std::vector<Card>& GetCards();

    private:
        std::vector<Card> cards;
};