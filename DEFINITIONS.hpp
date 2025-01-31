#pragma once

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900

#define SPLASH_STATE_SHOW_TIME 0.5

#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/res/Splash Background.png"
#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/res/Main Menu Background.png"
#define GAME_BACKGROUND_FILEPATH "Resources/res/Main Menu Background.png"
#define PAUSE_BACKGROUND_FILEPATH "Resources/res/Main Menu Background.png"
#define	SCORE "Resources/fonts/Marker Felt.ttf"
#define MAIN_MENU_TITLE_FILEPATH "Resources/res/Game Title.png"

#define MAIN_MENU_PLAY_BUTTON "Resources/res/Play Button.png"
#define RESUME_BUTTON "Resources/res/Resume Button.png"
#define HOME_BUTTON "Resources/res/Home Button.png"
#define RETRY_BUTTON "Resources/res/Retry Button.png"

#define MAIN_MENU_PLAY_BUTTON_OUTER "Resources/res/Play Button Outer.png"

#define PAUSE_BUTTON "Resources/res/Pause Button.png"

#define X_PIECE_FILEPATH "Resources/res/X.png"
#define O_PIECE_FILEPATH "Resources/res/O.png"
#define X_WINNING_PIECE_FILEPATH "Resources/res/X Win.png"
#define O_WINNING_PIECE_FILEPATH "Resources/res/O Win.png"

#define GRID_SPRITE_FILEPATH "Resources/res/Grid.png"

#define X_PIECE 8
#define O_PIECE 0
#define EMPTY_PIECE -1
#define FILLED_PIECE 1
#define PLAYER_PIECE X_PIECE
#define AI_PIECE O_PIECE

#define STATE_PLAYING 98
#define STATE_PAUSED 97
#define STATE_WON 96
#define STATE_LOSE 95
#define STATE_PLACING_PIECE 94
#define STATE_AI_PLAYING 93
#define STATE_DRAW 92
#define STATE_GAME_OVER_DELAY 91
#define STATE_TRANSITIONING 90
#define STATE_GAMEOVER 89