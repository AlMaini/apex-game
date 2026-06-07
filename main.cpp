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
    int max_hand_size = 10;

    ResourceManager resourceManager;
    Hand hand{window_x, window_y, 64.0f, max_hand_size};

    InitWindow(window_x, window_y, "Apex Game");

    Camera3D camera = {};
    camera.position   = {400.0f, 500.0f, 600.0f};
    camera.target     = {400.0f, 0.0f, -100.0f};
    camera.up         = {0.0f, 1.0f, 0.0f};
    camera.fovy       = 50.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    for (int i = 0; i < max_hand_size; ++i) {
        hand.AddCard(Card(resourceManager.GetTexture("assets/cat.png")));
    }

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();
        Ray ray = GetScreenToWorldRay(mousePos, camera);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        hand.Draw(camera);

        cout << "FPS: " << GetFPS() << endl;

        for (int i = 0; i < (int)hand.GetCards().size(); ++i) {
            if (hand.GetCards()[i].IsClicked(ray)) {
                cout << "Card clicked!" << endl;
                hand.GetCards()[i] = move(hand.GetCards().back());
                hand.GetCards().pop_back();
                break;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
