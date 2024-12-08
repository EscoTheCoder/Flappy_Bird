#pragma once

#include <vector>
#include "GameObject.h"
#include "Coin.h"
#include "Level.h"
#include "Start_Level.h"
#include "Coin_Score.h"
#include "Block.h"
#include "Player.h"
#include "Hearts.h"
#include "Extras.h"
#include <sgg/graphics.h>



class Level_2 : public GameObject, public Start_Level {
private:
    graphics::Brush m_brush_background;  // Brush for the game background
    graphics::Brush m_brush_ending_background;  // Brush for the ending background

    std::vector<Block> m_blocks;           // List of pipes in the level
    std::vector<Coin> m_coins;           // List of coins in the level
    std::vector<Extras> m_extras;

    std::vector<Hearts> m_hearts;        // List of heart images representing lives

    std::vector<Coin_Score> m_coin_score; // List of coins images representing scores

    bool m_game_paused = false; // Pause flag
    bool m_game_over = false;   // Game over flag
    float m_game_over_timer = 0.0f;  // Timer to delay game stop after game over

    int m_lives; // Variable to store lives
    int m_coins_for_score;

    void checkCollisions();   // Method to check for collisions
    void loseLife();          // Method to handle losing a life
    void loseCoin();

    typedef enum { STATUS_START, STATUS_PLAYING, STATUS_HELP} status_t;

    status_t status = STATUS_START;

    void updateStartScreen();
    void updateLevelScreen(float dt);
    void updateHelpScreen();

    void drawStartScreen();
    void drawLevelScreen();
    void drawHelpScreen();



public:

    int sum_coins = 0;

    Level_2(const std::string& name);
    ~Level_2();

    void init() override;     // Initialize the level
    void update(float dt) override;  // Update the level
    void draw() override;     // Draw the level

    void resetLevel();        // Method to reset the level


    /*friend ostream& operator<< (ostream& left, const vector<Coin_Score>& right) {

    }*/
};
