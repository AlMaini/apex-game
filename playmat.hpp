#pragma once

#include "card.hpp"
#include <vector>
#include <raylib.h>

class PlayMat{
    public:
        PlayMat(Vector2 startCoordinates, float width, float height);

        std::vector<Card>& GetCards();
        //Card GetCard(int index);
        void AddCard(Card& card);
        void RemoveCard(int index);

        bool IsFull();

        bool MouseOnPlayMat(Vector2 mousePos);
        void Draw();

    private:
        std::vector<Card> cards;
        Rectangle playArea;
        int maxCards;
        int hoveredIndex;
};