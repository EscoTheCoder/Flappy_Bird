#include "GameState.h"
#include "Player.h"
#include "Player_Level_2.h"
#include "Player_Level_3.h"
#include <thread>
#include <chrono>
#include <algorithm> // For std::max, std::min

using namespace std;

GameState::GameState() {
    // Constructor remains empty for now
}

GameState* GameState::getInstance() {
    static GameState instance;
    return &instance;
}

void GameState::init() {
    // Initialize levels
    level_1 = new Level("Level1");
    level_1->init();

    level_2 = new Level_2("Level2");  // Level_2 has its own constructor
    level_2->init();

    level_3 = new Level_3("Level3");  // Level_3 has its own constructor
    level_3->init();

    // Set current level to level 1 initially
    current_level = level_1;

    // Initialize player
    m_player = new Player("Bird");
    m_player->init();

    // Initialize player_2
    m_player_2 = new Player_Level_2("Square");
    m_player_2->init();

    m_player_3 = new Player_Level_3("Bird_2");
    m_player_3->init();

    // Preload assets
    //graphics::preloadBitmaps(getAssetDir());
}

void GameState::draw() {
    if (current_level) {
        current_level->draw();
    }
}

void GameState::update(float dt) {
    if (dt > 500) {
        return; // Ignore long delays
    }

    float sleep_time = max(0.0f, 17.0f - dt);
    this_thread::sleep_for(chrono::duration<float, milli>(sleep_time));

    if (current_level) {
        current_level->update(dt);
    }

    m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
}

void GameState::handleGameOver() {
    if (in_level_3) {
        // Game ends after level 3, so close the game
        graphics::stopMessageLoop(); // Exit the game loop
    }
    else if (in_level_2) {
        // Switch from level 2 to level 3
        in_level_3 = true;   // Indicate that we are now in level 3

        if (m_player_2) {
            delete m_player_2;   // Clean up the player for level 2
            m_player_2 = nullptr;  // Set pointer to nullptr to avoid double deletion
        }

        // Switch to Level 3
        current_level = level_3;  // Now in Level 3
    }
    else {
        // Switch from level 1 to level 2
        in_level_2 = true;   // Indicate that we are now in level 2

        if (m_player) {
            delete m_player;     // Clean up the player for level 1
            m_player = nullptr;  // Set pointer to nullptr to avoid double deletion
        }
        

        // Switch to Level 2
        current_level = level_2;  // Now in Level 2
    }
}



std::pair<float, float> GameState::getCanvasDimensions() const {
    return { m_canvas_width, m_canvas_height };
}

std::string GameState::getAssetDir() const {
    return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset) const {
    return m_asset_path + asset;
}

class Player* GameState::get_Player() const {
    return m_player;
}

void GameState::set_Player(class Player* player) {
    if (m_player) {
        delete m_player;
    }
    m_player = player;
}

Player_Level_2* GameState::get_Player_2() const {
    return m_player_2;
}

void GameState::set_Player_2(Player_Level_2* player) {
    if (m_player_2) {
        delete m_player_2;
    }
    m_player_2 = player;
}

Player_Level_3* GameState::get_Player_3() const {
    return m_player_3;
}

void GameState::set_Player_3(Player_Level_3* player) {
    if (m_player_3) {
        delete m_player_3;
    }
    m_player_3 = player;
}

GameState::~GameState() {
    // Clean up dynamically allocated memory for levels
    if (level_1) {
        delete level_1;
        level_1 = nullptr;
    }
    if (level_2) {
        delete level_2;
        level_2 = nullptr;
    }
    if (level_3) {
        delete level_3;
        level_3 = nullptr;
    }

    // Clean up players
    if (m_player) {
        delete m_player;
        m_player = nullptr;
    }
    if (m_player_2) {
        delete m_player_2;
        m_player_2 = nullptr;
    }
    if (m_player_3) {
        delete m_player_3;
        m_player_3 = nullptr;
    }
}

