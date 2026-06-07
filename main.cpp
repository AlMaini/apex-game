#include <iostream>
#include <vector>
#include <raylib.h>

#include "resource_manager.hpp"
#include "card.hpp"
#include "hand.hpp"

using namespace std;

int main() {

    int window_x = 800;
    int window_y = 800;
    int fps = 320;
    int max_hand_size = 10;

    // SetTargetFPS(fps);

    ResourceManager resourceManager;
    Hand hand{window_x, window_y, 64.0f, max_hand_size};

    InitWindow(window_x, window_y, "Apex Game");

    for(int i = 0; i < max_hand_size; ++i) {
        hand.AddCard(Card(resourceManager.GetTexture("assets/cat.png")));
    }

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // cout << "\rFrame time: " << GetFrameTime() << flush;

        hand.Draw();

        for (int i = 0; i < hand.GetCards().size(); ++i) {
            if (hand.GetCards()[i].IsClicked(mousePos)) {
                cout << "Card clicked!" << endl;
                // hand.RemoveAt(i);
                break;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}