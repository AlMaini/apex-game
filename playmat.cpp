#include <vector>

#include "playmat.hpp"
#include "card.hpp"

PlayMat::PlayMat(Vector2 startCoordinates, float width, float height){
    playArea = Rectangle{startCoordinates.x, startCoordinates.y, width, height};
    cards = std::vector<Card>();
}

std::vector<Card>& PlayMat::GetCards(){
    return cards;
}

void PlayMat::AddCard(Card& card){
    cards.push_back(card);
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
}