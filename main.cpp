#include <iostream>
#include <vector>
#include <raylib.h>

#include "resource_manager.hpp"
#include "card.hpp"
#include "hand.hpp"

using namespace std;

int main() {

    ResourceManager resourceManager;
    Hand hand;

    InitWindow(800, 800, "Apex Game");

    for(int i = 0; i < 5; ++i) {
        hand.AddCard(Card(resourceManager.GetTexture("assets/cat.png"), Vector2{100.0f + i * 150.0f, 600.0f}));
    }

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        hand.Draw();

        for (int i = 0; i < hand.GetCards().size(); ++i) {
            if (hand.GetCards()[i].IsClicked(mousePos)) {
                cout << "Card clicked!" << endl;
                hand.GetCards()[i] = move(hand.GetCards().back());
                hand.GetCards().pop_back();
            }
        }
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}