#include "raylib.h"

// Types and Structures Definition
typedef enum GameScreen {TITLE, GAMEPLAY} GameScreen;

const int screenWidth = 800;
const int screenHeight = 450;

//se sim, retorna 1. se não, retorna 0
int CheckButton(Vector2 mousePoint, Rectangle recButton, Sound clickSound) {
    
    if (CheckCollisionPointRec(mousePoint, recButton)) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { 
            PlaySound(clickSound);
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");
    InitAudioDevice();

    GameScreen currentScreen = TITLE;

    Texture2D button = LoadTexture("resourses\\button.png");
    Texture2D background = LoadTexture("resourses\\country-platform-preview.png");
    Sound clickSound = LoadSound("resourses\\MenuClick.wav");
    SetTargetFPS(60);

    button.height = button.height/3.0;
    button.width = button.width/3.0;
    background.height = screenHeight;
    background.width = screenWidth;

    Rectangle player = { 420, 245, 40, 40 };
    Camera2D camera = { 0 };
    camera.target = (Vector2) {player.x + 20, player.y + 20};
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Vector2 mousePoint = { 0.0f, 0.0f };
    Rectangle recButtonTitle = {screenWidth/4.0f - button.width/2.0f, screenHeight/4.0f - button.height/2.0f, button.width, button.height};
    Rectangle recButtonGameplay = {screenWidth - 200, screenHeight - 90, button.width, button.height};

    float scrollTitleScreen = 0.0f;
    float velScroll = 0.5f;
    Rectangle playerRect;
    
    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_DOWN)) player.y += 2;
        if (IsKeyDown(KEY_UP)) player.y -= 2;
        if (IsKeyDown(KEY_LEFT)) player.x -= 2;
        if (IsKeyDown(KEY_RIGHT)) player.x += 2;

        playerRect = (Rectangle) {player.x - 20, player.y - 20, 40, 40};

        mousePoint = GetMousePosition();
        scrollTitleScreen -= velScroll;
        if (scrollTitleScreen <= -screenWidth) scrollTitleScreen = 0.0f;

        switch(currentScreen)
        {
            case TITLE:
            {
               if (CheckButton(mousePoint, recButtonTitle, clickSound)) currentScreen = GAMEPLAY;
            } break;

            case GAMEPLAY:
            {
                camera.target = (Vector2) {player.x, player.y};
                camera.zoom += ((float)GetMouseWheelMove()*0.05f);

                if (camera.zoom > 3.0f) camera.zoom = 3.0f;
                else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

                if (CheckButton(mousePoint, recButtonGameplay, clickSound)) currentScreen = TITLE;
            } break;
            default: break;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case TITLE:
                {
                    ClearBackground(RAYWHITE);
                    DrawTexture(background, scrollTitleScreen, 0, WHITE);
                    DrawTexture(background, scrollTitleScreen + screenWidth, 0, WHITE);
                    DrawTexture(button, screenWidth/4.0f - button.width/2.0f, screenHeight/4.0f - button.height/2.0f, WHITE);
                    DrawText("PLAY", screenWidth/4.0f + button.width/1.5f, screenHeight/4.0f - button.height/4.0f, button.height/2, BLACK);
                } break;
                case GAMEPLAY:
                {                    
                    BeginMode2D(camera);

                        ClearBackground(BLACK);
                        DrawRectangle(50, 50, 700, 350, WHITE);
                        DrawRectangleRec(playerRect, RED);

                    EndMode2D();

                    DrawTexture(button, screenWidth - 200, screenHeight - 90, WHITE);
                    DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
                    DrawText("BACK", screenWidth - 200 + button.width * 1.2, screenHeight - 90 + button.height/4.0f, button.height/2, BLUE);
                } break;
                default: break;
            }

        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}
