#pragma once

#include <vector>
#include "GameObject.h"
#include "Start_Level.h"
#include "Kills.h"
#include "Block.h"
#include "Player.h"
#include "Enemy.h"
#include "Hearts.h"
#include <sgg/graphics.h>



class Level_3 : public GameObject, public Start_Level {
private:
    graphics::Brush m_brush_background;  // Brush for the game background
    graphics::Brush m_brush_ending_background;  // Brush for the ending background

    std::vector<Block> m_blocks;           // List of block in the level
    std::vector<Enemy> m_enemies;           // List of enemies in the level
    std::vector<Enemy> m_extras;

    std::vector<std::string> enemy_textures = { "w1.png", "w2.png", "w3.png", "w4.png" };


    std::vector<Kills> m_kills;

    std::vector<Hearts> m_hearts;        // List of heart images representing lives

    bool m_game_paused = false; // Pause flag
    bool m_game_over = false;   // Game over flag
    float m_game_over_timer = 0.0f;  // Timer to delay game stop after game over

    int m_lives; // Variable to store lives
    int m_kills_for_score;

    void checkCollisions();   // Method to check for collisions
    void loseLife();          // Method to handle losing a life
    void KillEnemy();

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

    Level_3(const std::string& name);
    ~Level_3();

    void init() override;     // Initialize the level
    void update(float dt) override;  // Update the level
    void draw() override;     // Draw the level

    void resetLevel();        // Method to reset the level


    /*friend ostream& operator<< (ostream& left, const vector<Coin_Score>& right) {

    }*/
};
