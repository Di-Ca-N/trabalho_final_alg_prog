#include "graphics.h"

#include <stdio.h> // snprintf
#include <string.h> // strlen
#include "raylib.h"

void initGraphics() {
    // Init game window
    InitWindow(
        TILE_SIZE * NUM_TILES_WIDTH, 
        TILE_SIZE * NUM_TILES_HEIGHT, 
        "Dangerous Dave");

    // Set game to run at 60 fps
    SetTargetFPS(60);

    // Remove default exit key
    SetExitKey(0);
}

// Draw a menu to the screen, starting at xPos and yPos
void drawMenu(Menu menu, int xPos, int yPos) {
    // Loop to draw menu options
    for (int i = 0; i < menu.numOptions; i++) {
        // Buffer to hold option text. Set to MAX_OPTION_LENGTH + 2 to 
        // account for extra characters added to the buffer on the "if" below
        char optionBuffer[MAX_OPTION_LENGTH + 2];

        // If the option being current redendered is the selected option
        if (menu.selectedOption == i) {
            // Add a marker to the option
            snprintf(optionBuffer, MAX_OPTION_LENGTH + 2, 
                     "> %s", menu.options[i]);
        } else {
            // Otherwise, add no mark
            snprintf(optionBuffer, MAX_OPTION_LENGTH + 2, "  %s", 
                     menu.options[i]);
        }
        // Draw option text to screen
        int itemYPos = yPos + 2 + i * TEXT_FONT_SIZE;
        DrawText(optionBuffer, xPos, itemYPos, TEXT_FONT_SIZE, BLACK);
    }
}

// Render the main menu scren
void renderMainMenu(Menu menu) {
    // Start drawing
    BeginDrawing();

    // Clear background
    ClearBackground(RAYWHITE);
    
    // Draw menu title
    DrawText("Dangerous Dave", TILE_SIZE * 3, TILE_SIZE * 3, 
             HEADER_FONT_SIZE, BLACK);

    // Draw menu options
    drawMenu(menu, TILE_SIZE * 3, TILE_SIZE * 3 + HEADER_FONT_SIZE + 10);

    // End drawing
    EndDrawing();
}

// Render the ranking screen
void renderRanking(Ranking ranking, Menu menu) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Ranking", TILE_SIZE * 3, TILE_SIZE * 3, HEADER_FONT_SIZE, BLACK);

    char rankingEntryBuffer[MAX_USERNAME_LENGTH + 12];

    for (int i = 0; i < 5; i++) {
        if (strlen(ranking.entries[i].username) == 0) {
            snprintf(
                rankingEntryBuffer,
                MAX_USERNAME_LENGTH + 12,
                "%d. %10s    %04d",
                i + 1,
                "---",
                ranking.entries[i].score);
        } else {
            snprintf(
                rankingEntryBuffer, 
                MAX_USERNAME_LENGTH + 12, 
                "%d. %10s    %04d", i + 1, 
                ranking.entries[i].username, 
                ranking.entries[i].score);
        }
        
        DrawText(
            rankingEntryBuffer, 
            TILE_SIZE * 3, 
            TILE_SIZE * 3 + HEADER_FONT_SIZE + 12 + i * TEXT_FONT_SIZE, 
            TEXT_FONT_SIZE, 
            BLACK);
    }
    int menuYPos = TILE_SIZE * 3 + HEADER_FONT_SIZE + 10 + 5 * TEXT_FONT_SIZE;
    drawMenu(menu, TILE_SIZE * 3, menuYPos);
    EndDrawing();
}

void renderGame(Game game) {
    SetWindowSize(game.map.width * TILE_SIZE, game.map.height * TILE_SIZE);
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int row = 0; row < game.map.height; row++) {
        for (int col = 0; col < game.map.width; col++) 
        {
            if (game.map.stage[row][col] == 'x') {
                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);
            }
            if  (game.map.stage[row][col] == '%') {  // Coroa
                DrawCircle(col * TILE_SIZE + (TILE_SIZE / 2) , row * TILE_SIZE + (TILE_SIZE / 2) , (TILE_SIZE / 2) , GOLD); 
            }
            if  (game.map.stage[row][col] == '#') {  // Rubi
                
                Vector2 v1 = { (col + 0.5) * TILE_SIZE , row  * TILE_SIZE};
                Vector2 v2 = {col * TILE_SIZE , (row + 1)  * TILE_SIZE};
                Vector2 v3 = { (col + 1) * TILE_SIZE , (row + 1)  * TILE_SIZE};
                
                DrawTriangle ( v1 , v2 , v3 , GREEN); 
             }
            if  (game.map.stage[row][col] == '!') {  // Ametista
                DrawRectangle( col * TILE_SIZE , row * TILE_SIZE  , TILE_SIZE  , (TILE_SIZE / 2) ,  PURPLE); 
            }
         }
    }

    DrawRectangle(game.dave.position.x * TILE_SIZE, game.dave.position.y * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);
    EndDrawing();
}


void endGraphics() {
    CloseWindow();
}
