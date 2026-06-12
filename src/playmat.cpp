#include <vector>

#include "playmat.hpp"
#include "card.hpp"

PlayMat::PlayMat(Vector2 startCoordinates, float width, float height){
    playArea = Rectangle{startCoordinates.x, startCoordinates.y, width, height};
    cards = std::vector<Card>();
    maxCards = 4;
    hoveredIndex = -1;
}

std::vector<Card>& PlayMat::GetCards(){
    return cards;
}

bool PlayMat::IsFull(){
    return cards.size() == maxCards;
}

void PlayMat::AddCard(Card& card){
    if (IsFull()) return;

    Rectangle lastRect = cards.empty() ? Rectangle{150.0f, 250.0f, 64.0f, 0.0f} : cards.back().GetRect();
    cards.push_back(card);
    cards.back().SetState(CardState::Idle);
    cards.back().SetPosition({lastRect.x + lastRect.width + 15.0f, lastRect.y});
    cards.back().SetParams(CardState::Hovered, { 5.0f, 0.05f, 10.0f, 1.2f });
}

void PlayMat::RemoveCard(int index){
    int back = (int)cards.size() - 1;
    cards[index] = std::move(cards.back());
    cards.pop_back();
}

bool PlayMat::MouseOnPlayMat(Vector2 mousePos){
    return CheckCollisionPointRec(mousePos, playArea);
}

void PlayMat::Draw(){
    DrawRectangle(playArea.x, playArea.y, playArea.width, playArea.height, GRAY);

    Vector2 mousePos = GetMousePosition();
    int newHovered = -1;
    for (int i = (int)cards.size() - 1; i >= 0; --i) {
        if (cards[i].IsHovered(mousePos)) { newHovered = i; break; }
    }

    if (hoveredIndex != newHovered) {
        if (hoveredIndex != -1) cards[hoveredIndex].SetState(CardState::Idle);
        if (newHovered   != -1) cards[newHovered].SetState(CardState::Hovered);
        hoveredIndex = newHovered;
    }

    for (int i = 0; i < (int)cards.size(); ++i)
        if (i != hoveredIndex) cards[i].Draw();
    if (hoveredIndex != -1) cards[hoveredIndex].Draw();
}