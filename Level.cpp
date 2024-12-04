#include "Level.h"
#include "GameState.h"
#include "Coin_Score.h"
#include "Player.h"
#include <sgg/graphics.h>
#include <iostream>
#include "util.h"

using namespace std;

Level::Level(const string& name) :
    GameObject(name), m_lives(3) , Start_Level("level1") { // Initialize with 3 lives
}

Level::~Level() {
    // Clear pipes
    m_pipes.clear();

    // Clear coins
    m_coins.clear();

    // Clear hearts
    m_hearts.clear();

    // Clear coin score objects
    m_coin_score.clear();

    // Optionally log destruction for debugging
    std::cout << "Level 1 destroyed: " << std::endl;
}



void Level::init() {
    m_lives = 3; // Reset to 3 lives
    m_coins_for_score = 3;
    m_game_over = false; // Reset game-over flag
    m_game_over_timer = 0.0f; // Reset game-over timer

    // Initialize background
    m_brush_background.outline_opacity = 0.0f;
    m_brush_background.texture = m_state->getFullAssetPath("sky.png");

    // Initialize ending background
    m_brush_ending_background.outline_opacity = 0.0f;
    m_brush_ending_background.texture = m_state->getFullAssetPath("gameover.png");



    // Initialize pipes with positions and textures


    m_pipes.emplace_back(7.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(7.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(10.0f, 5.50f, 1.0f, 2.0f, "pipe_up.png");
    m_pipes.emplace_back(10.0f, 1.0f, 1.0f, 4.0f, "pipe_down.png");

    m_pipes.emplace_back(13.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(13.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(16.0f, 5.50f, 1.0f, 2.0f, "pipe_up.png");
    m_pipes.emplace_back(16.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(19.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(19.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(22.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(22.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(25.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(25.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(28.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(28.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(31.0f, 5.50f, 1.0f, 2.0f, "pipe_up.png");
    m_pipes.emplace_back(31.0f, 1.0f, 1.0f, 4.0f, "pipe_down.png");

    m_pipes.emplace_back(34.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(34.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(37.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(37.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(40.0f, 5.50f, 1.0f, 2.0f, "pipe_up.png");
    m_pipes.emplace_back(40.0f, 1.0f, 1.0f, 4.0f, "pipe_down.png");

    m_pipes.emplace_back(43.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(43.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(46.0f, 5.50f, 1.0f, 2.0f, "pipe_up.png");
    m_pipes.emplace_back(46.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(49.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(49.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(52.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(52.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(55.0f, 5.50f, 1.0f, 4.0f, "pipe_up.png");
    m_pipes.emplace_back(55.0f, 1.0f, 1.0f, 2.0f, "pipe_down.png");

    m_pipes.emplace_back(58.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(58.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");

    m_pipes.emplace_back(61.0f, 5.50f, 1.0f, 2.0f, "pipe_up.png");
    m_pipes.emplace_back(61.0f, 1.0f, 1.0f, 4.0f, "pipe_down.png");

    m_pipes.emplace_back(64.0f, 5.50f, 1.0f, 3.0f, "pipe_up.png");
    m_pipes.emplace_back(64.0f, 1.0f, 1.0f, 3.0f, "pipe_down.png");


  


    for (auto& pipe : m_pipes) {
        pipe.init();
    }

    // Initialize coins
    m_coins.emplace_back(7.0f, 3.2f, 1.0f, 1.0f, 5.0f, "Bronze-Medal.png");
    m_coins.emplace_back(34.0f, 3.2f, 1.0f, 1.0f, 5.0f, "Silver-Medal.png");
    m_coins.emplace_back(64.0f, 3.2f, 1.0f, 1.0f, 5.0f, "Gold-Medal.png");
    m_coins.emplace_back(72.0f, 2.7f, 2.0f, 2.0f, 5.0f, "portal.png");
    m_coins.emplace_back(76.0f, 2.5f, 2.0f, 15.0f, 5.0f, "finish_line.png");

    for (auto& coin : m_coins) {
        coin.init();
    }

    // Position the hearts at the top-left corner
    float heart_pos_x = 0.3f;  // Positioned near the left edge of the canvas
    float heart_pos_y = 0.3f;  // Positioned near the top edge of the canvas
    float heart_spacing = 0.05f; // Space between hearts

    m_hearts.clear();
    for (int i = 0; i < m_lives; ++i) {
        m_hearts.emplace_back(heart_pos_x + i * (0.3f + heart_spacing), heart_pos_y, 0.3f, 0.3f, "heart.png"); // Example size of 0.3x0.3
    }

    for (auto& heart : m_hearts) {
        heart.init();
    }

    // Position the coins at the top-left corner
    float coin_score_pos_x = 0.3f;  // Positioned near the left edge of the canvas
    float coin_score_pos_y = 0.7f;  // Positioned near the top edge of the canvas
    float coin_score_spacing = 0.05f; // Space between hearts

    m_coin_score.clear();
    for (int i = 0; i < m_lives; ++i) {
        m_coin_score.emplace_back(coin_score_pos_x + i * (0.3f + coin_score_spacing), coin_score_pos_y, 0.3f, 0.3f, "coin_for_score.png"); // Example size of 0.3x0.3
    }

    for (auto& coin_score : m_coin_score) {
        coin_score.init();
    }
}



void Level::update(float dt) {

    if (status == STATUS_START) {
        updateStartScreen();
    }
    else if(status == STATUS_PLAYING) {
        updateLevelScreen(dt);
    }
    else if (status == STATUS_HELP) {
        updateHelpScreen();
    }
}

void Level::updateStartScreen() {

    graphics::MouseState mouse;
    graphics::getMouseState(mouse);

    if (graphics::getKeyState(graphics::SCANCODE_SPACE) || mouse.button_left_pressed) {

        status = STATUS_PLAYING;
    }
    else if (graphics::getKeyState(graphics::SCANCODE_H)) {

        status = STATUS_HELP;
    }
}

void Level::updateHelpScreen() {
    graphics::MouseState mouse;
    graphics::getMouseState(mouse);

    if (graphics::getKeyState(graphics::SCANCODE_T) || mouse.button_left_pressed) {

        status = STATUS_START;
    }
    else {
        status = STATUS_HELP;
    }
}


void Level::updateLevelScreen(float dt) {

    if (m_game_paused) {
        graphics::MouseState mouse;
        graphics::getMouseState(mouse);

        if (graphics::getKeyState(graphics::SCANCODE_SPACE) || mouse.button_left_pressed) {
            resetLevel();
        }
        return;
    }

    // If the game is over, start the timer to delay the ending
    if (m_game_over) {
        m_game_over_timer += dt;
        // Display game-over prompt for 2 seconds and wait for user input
        if (m_game_over_timer > 2000.0f) { // After 2 seconds, allow player to continue
            /*graphics::MouseState mouse;
            graphics::getMouseState(mouse);
            if (graphics::getKeyState(graphics::SCANCODE_SPACE) || mouse.button_left_pressed) {
                m_state->handleGameOver();
                return;
            }*/
            graphics::stopMessageLoop();
        }
        return;  // Wait for player input before starting next level
    }


    // Update player
    if (m_state->get_Player() && m_state->get_Player()->isActive()) {
        m_state->get_Player()->update(dt);
    }

    // Update pipes
    for (auto& pipe : m_pipes) {
        pipe.update(dt);
    }

    // Update coins
    for (auto& coin : m_coins) {
        coin.update(dt);
    }

    /*for (auto& final_coin : m_coins) {
        final_coin.update(dt);
    }*/


    //// Update coins_score
    //for (auto& coins_score : m_coin_score) {
    //    coins_score.update(dt);
    //}

    checkCollisions();

    GameObject::update(dt);
}




void Level::draw() {

    if (status == STATUS_START) {
        drawStartScreen();
    }
    else if (status == STATUS_PLAYING) {
        drawLevelScreen();
    }
    else if (status == STATUS_HELP) {
        drawHelpScreen();
    }
}


void Level::drawStartScreen() {
    graphics::Brush br;

    float w = m_state->getCanvasDimensions().first;
    float h = m_state->getCanvasDimensions().second;

    float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
    float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

    br.outline_opacity = 0.0f;
    br.texture = m_state->getFullAssetPath("loading_lvl1.png");
    // Draw background
    graphics::drawRect(offset_x, offset_y, w, h, br);

}

void Level::drawHelpScreen() {
    graphics::Brush br;

    float w = m_state->getCanvasDimensions().first;
    float h = m_state->getCanvasDimensions().second;

    float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
    float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

    br.outline_opacity = 0.0f;
    br.texture = m_state->getFullAssetPath("settings_lvl_1.png");
    // Draw background
    graphics::drawRect(offset_x, offset_y, w, h, br);
}

void Level::drawLevelScreen() {
    float w = m_state->getCanvasDimensions().first;
    float h = m_state->getCanvasDimensions().second;

    float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
    float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

    // Draw the ending background with smaller dimensions
    float ending_bg_width = w * 0.8f; // 70% of the canvas width
    float ending_bg_height = h * 0.3f; // 70% of the canvas height

    // Draw background
    graphics::drawRect(offset_x, offset_y, w, h, m_brush_background);

    if (!m_game_over) {
        // Draw player
        if (m_state->get_Player()->isActive()) {
            m_state->get_Player()->draw();
        }

        // Draw pipes
        for (auto& pipe : m_pipes) {
            pipe.draw();
        }

        // Draw coins
        for (auto& coin : m_coins) {
            coin.draw();
        }

        //// Draw extras
        //for (auto& extras : m_extras) {
        //    extras.draw();
        //}

        // Draw hearts (lives) on the left side of the canvas
        for (auto& heart : m_hearts) {
            heart.draw();
        }

        // Draw coin (score) on the left side of the canvas
        for (auto& coin_score : m_coin_score) {
            coin_score.draw();
        }
    }
    else {
        //// If the game is over, draw the ending background and "Press Space to Continue"
        //float ending_bg_width = w * 0.8f; // Adjust to desired width
        //float ending_bg_height = h * 0.3f; // Adjust to desired height

        graphics::drawRect(offset_x, offset_y, ending_bg_width, ending_bg_height, m_brush_ending_background);

        //graphics::Brush br;
        //SETCOLOR(br.fill_color,1.0f,1.0f,1.0f);
        //br.fill_opacity = 1.0f;
        //br.outline_opacity = 0.0f;

        //graphics::drawText(offset_x - 0.2f * w, offset_y + 0.1f * h, 30.0f, "Press SPACE to continue", br);
        //m_state->handleGameOver();
    }
}



void Level::loseLife() {
    if (m_lives > 0) {
        m_lives--;

        // Remove a heart visually by popping the last heart from the list
        m_hearts.pop_back();

        if (m_lives == 0) {
            m_game_over = true;
            //m_state->handleGameOver();
        }
    }
}

void Level::loseCoin() {
    if (m_coins_for_score > 0) {
        m_coins_for_score--;

        // Remove a coin visually by popping the last coin from the list
        m_coin_score.pop_back();

        /*if (m_coins_for_score == 0) {
            m_game_over = true;
        }*/
    }
}



void Level::resetLevel() {
    // Reset player and other objects (existing code)

    Player* player = m_state->get_Player();
    player->reset();

    // Reset pipes
    for (auto& pipe : m_pipes) {
        pipe.reset();
    }

    // Reset coins
    m_coins.clear();
    m_coins.emplace_back(7.0f, 3.2f, 1.0f, 1.0f, 5.0f, "Bronze-Medal.png");
    m_coins.emplace_back(34.0f, 3.2f, 1.0f, 1.0f, 5.0f, "Silver-Medal.png");
    m_coins.emplace_back(64.0f, 3.2f, 1.0f, 1.0f, 5.0f, "Gold-Medal.png");
    m_coins.emplace_back(72.0f, 2.7f, 2.0f, 2.0f, 5.0f, "portal.png");
    m_coins.emplace_back(76.0f, 2.5f, 2.0f, 15.0f, 5.0f, "finish_line.png");

    for (auto& coin : m_coins) {
        coin.init();
    }

    //// Reset extras
    ////m_extras.emplace_back(75.0f, 3.2f, 2.0f, 5.0f, "do_not_stop_image.png");
    //m_extras.emplace_back(70.0f, 2.5f, 2.0f, 15.0f, "portal.png");
    //for (auto& extras : m_extras) {
    //    extras.init();
    //}

    // Reset hearts' position at the top-left corner
    m_hearts.clear(); // Clears but doesn’t free memory

    float heart_pos_x = 0.3f;  // Positioned near the left edge of the canvas
    float heart_pos_y = 0.3f;  // Positioned near the top edge of the canvas
    float heart_spacing = 0.05f; // Space between hearts

    for (int i = 0; i < m_lives; ++i) {
        m_hearts.emplace_back(heart_pos_x + i * (0.3f + heart_spacing), heart_pos_y, 0.3f, 0.3f, "heart.png"); // Example size of 0.3x0.3
    }

    for (auto& heart : m_hearts) {
        heart.init();
    }

    // Reset coin_score's position at the top-left corner
    m_coin_score.clear(); // Clears but doesn’t free memory

    // Position the coins at the top-left corner
    float coin_score_pos_x = 0.3f;  // Positioned near the left edge of the canvas
    float coin_score_pos_y = 0.7f;  // Positioned near the top edge of the canvas
    float coin_score_spacing = 0.05f; // Space between hearts

    for (int i = 0; i < 3; ++i) { // <3 gia na einai panta 3 ta coins_for_score meta to reset
        m_coin_score.emplace_back(coin_score_pos_x + i * (0.3f + coin_score_spacing), coin_score_pos_y, 0.3f, 0.3f, "coin_for_score.png"); // Example size of 0.3x0.3
    }

    for (auto& coin_score : m_coin_score) {
        coin_score.init();
    }

    m_game_paused = false;
}


void Level::checkCollisions() {
    if (m_game_paused || m_game_over) return;

    Player* player = m_state->get_Player();
    if (!player) {
        std::cerr << "Player not initialized!" << std::endl;
        return;
    }

    // Check pipe collisions
    for (auto& pipe : m_pipes) {
        if (player->intersect(pipe)) {
            player->dead_player_change_photo();
            graphics::playSound(m_state->getFullAssetPath("hit.wav"), 0.5f);
            loseLife();
            m_game_paused = true;
            return;
        }
    }

    // Check coin collisions
    auto it = m_coins.begin();
    while (it != m_coins.end()) {
        if (player->intersect(*it)) {
            if (it->getTexture() == "finish_line.png") {
                player->dead_player_change_photo();
                graphics::playSound(m_state->getFullAssetPath("hit.wav"), 0.5f);
                loseLife();
                m_game_paused = true;
                return;
            }
            else if (it->getTexture() == "portal.png") {
                graphics::playSound(m_state->getFullAssetPath("lets_go.wav"), 0.5f);
                it = m_coins.erase(it); // Remove the finish line
                m_game_over = true; // End the game when the finish line is hit
                m_state->handleGameOver();  // Handle the transition or close the game
                return;
            }
            graphics::playSound(m_state->getFullAssetPath("coin.wav"), 0.5f);
            loseCoin(); // Decrease the coin count
            it = m_coins.erase(it); // Remove the collected coin
            
        }
        else {
            ++it;
        }
    }



    // Check if the player hits the ground
    float floorY = m_state->getCanvasDimensions().second - 0.1f;
    if (player->m_pos_y > floorY) {
        graphics::playSound(m_state->getFullAssetPath("hit.wav"), 0.5f);
        loseLife();
        m_game_paused = true;
    }
}
