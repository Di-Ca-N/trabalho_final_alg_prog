// Header guard to avoid redefinitions
#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "maps.h"

// Game related structs

typedef struct {
    // Dave position and speed
    Vector2 position;
    Vector2 speed;

    int lives;

    // State flags
    bool jumping;
    bool flying;
    bool gotTrophy;
    bool hasJetpack;

    // Frame update acumulators
    Vector2 dFramePosition;
    Vector2 dFrameSpeed;
} Dave;

typedef struct {
    // Dave and Map representations
    Dave dave;
    Map map;

    // Current player score
    int score;

    // Current stage number
    int stage;

    // Physics related variables
    float gravity;
} Game;

// Recognized game actions. Defined to decouple keyboard input from game actions
typedef enum {
    ACTION_UP = 1, ACTION_DOWN, ACTION_LEFT, ACTION_RIGHT,
    ACTION_EXIT, ACTION_SAVE, ACTION_STOP, 
    ACTION_RELEASE_UP, ACTION_RELEASE_DOWN, 
    ACTION_RELEASE_RIGHT, ACTION_RELEASE_LEFT,
    ACTION_YES, ACTION_NO,
} Action;

Game newGame();                                               // Create a new game
Game handleAction(Game game, Action action, double time);     // Update game state according to actions
Game updatePhysics(Game game, double time);                   // Apply physics updates on game

// Menus
#define MAX_MENU_LENGTH 4
#define MAX_OPTION_LENGTH 20

typedef struct {
    char options[MAX_MENU_LENGTH][MAX_OPTION_LENGTH];
    int numOptions;
    int selectedOption;
    bool selectionDone;
} Menu;

typedef enum {
    MENU_MAIN, MENU_EXIT, MENU_RANKING
} MenuType;

Menu getMenu(MenuType type);                 // Create a menu from given type
Menu updateMenu(Menu menu, Action action);   // Update menu state based on action

#endif
