#include "Level_2.h"
#include "GameState.h"
#include "Coin_Score.h"
#include "Player_Level_2.h"
#include <sgg/graphics.h>
#include <iostream>

using namespace std;

Level_2::Level_2(const string& name) :
    GameObject(name), m_lives(3), Start_Level("Level2") { // Initialize with 3 lives
}

Level_2::~Level_2() {
    // Clear blocks
    m_blocks.clear();

    // Clear triangles
    m_extras.clear();

    // Clear coins
    m_coins.clear();

    // Clear hearts
    m_hearts.clear();

    // Clear coin score objects
    m_coin_score.clear();

    // Optionally log destruction for debugging
    std::cout << "Level 2 destroyed: " << std::endl;
}


void Level_2::init() {
    m_lives = 3; // Reset to 3 lives
    m_coins_for_score = 3;
    m_game_over = false; // Reset game-over flag
    m_game_over_timer = 0.0f; // Reset game-over timer

    // Initialize background
    m_brush_background.outline_opacity = 0.0f;
    m_brush_background.texture = m_state->getFullAssetPath("background.png");

    // Initialize ending background
    m_brush_ending_background.outline_opacity = 0.0f;
    m_brush_ending_background.texture = m_state->getFullAssetPath("gameover.png");



    // Initialize pipes with positions and textures



    for (int i = 0; i < 150; i++) {
        //m_extras.emplace_back((float)i, 5.50f, 1.0f, 1.0f, "Ground.png");
        m_blocks.emplace_back((float)i, 5.50f, 1.1f, 1.1f, "obstacleSquare.png");
    }


    m_extras.emplace_back(7.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_extras.emplace_back(8.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_extras.emplace_back(8.5f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_extras.emplace_back(14.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_blocks.emplace_back(15.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_extras.emplace_back(16.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_extras.emplace_back(17.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_blocks.emplace_back(18.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_extras.emplace_back(19.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_extras.emplace_back(20.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_blocks.emplace_back(21.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(21.0f, 3.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_extras.emplace_back(27.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_blocks.emplace_back(28.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(29.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(30.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(31.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_extras.emplace_back(32.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_extras.emplace_back(33.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_blocks.emplace_back(34.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(35.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_extras.emplace_back(36.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_extras.emplace_back(37.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_blocks.emplace_back(37.0f, 3.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_extras.emplace_back(38.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_blocks.emplace_back(39.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(39.0f, 3.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(40.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(40.0f, 3.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(41.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(41.0f, 3.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(42.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(42.0f, 3.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_extras.emplace_back(42.0f, 2.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_blocks.emplace_back(43.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(43.0f, 3.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(44.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(44.0f, 3.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(45.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(45.0f, 3.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_extras.emplace_back(45.0f, 2.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_extras.emplace_back(46.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_extras.emplace_back(47.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_blocks.emplace_back(47.0f, 3.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_extras.emplace_back(48.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_extras.emplace_back(49.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_blocks.emplace_back(50.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(51.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_blocks.emplace_back(52.0f, 4.50f, 1.0f, 1.1f, "obstacleSquare.png");
    m_extras.emplace_back(53.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");
    m_extras.emplace_back(54.0f, 4.8f, 0.5f, 0.5f, "obstacleTriangle.png");



    for (auto& block : m_blocks) {
        block.init();
    }


    // Initialize coins
    m_coins.emplace_back(21.0f, 2.5f, 0.5f, 0.5f, 3.0f, "coin.png");
    m_coins.emplace_back(29.0f, 3.5f, 0.5f, 0.5f, 3.0f, "coin.png");
    m_coins.emplace_back(52.0f, 3.5f, 0.5f, 0.5f, 3.0f, "coin.png");

    for (auto& coin : m_coins) {
        coin.init();
    }

    //m_extras.emplace_back(75.0f, 3.2f, 2.0f, 5.0f, "do_not_stop_image.png");
    m_extras.emplace_back(58.0f, 2.5f, 2.0f, 2.0f, "portal.png");

    for (auto& extras : m_extras) {
        extras.init();
    }

    // Position the hearts at the top-left corner
    float heart_pos_x = 0.3f;  // Positioned near the left edge of the canvas
    float heart_pos_y = 0.3f;  // Positioned near the top edge of the canvas
    float heart_spacing = 0.05f; // Space between hearts

    m_hearts.clear();
    for (int i = 0; i < m_lives; ++i) {
        m_hearts.emplace_back(heart_pos_x + i * (0.3f + heart_spacing), heart_pos_y, 0.3f, 0.3f, "heart_2.png"); // Example size of 0.3x0.3
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
        m_coin_score.emplace_back(coin_score_pos_x + i * (0.3f + coin_score_spacing), coin_score_pos_y, 0.3f, 0.3f, "coin.png"); // Example size of 0.3x0.3
    }

    for (auto& coin_score : m_coin_score) {
        coin_score.init();
    }
}



void Level_2::update(float dt) {

    if (status == STATUS_START) {
        updateStartScreen();
    }
    else if (status == STATUS_PLAYING) {
        updateLevelScreen(dt);
    }
    else if (status == STATUS_HELP) {
        updateHelpScreen();
    }
}

void Level_2::updateStartScreen() {

    //graphics::playSound(m_state->getFullAssetPath("arapis.wav"), 0.009f);

    graphics::MouseState mouse;
    graphics::getMouseState(mouse);

    if (graphics::getKeyState(graphics::SCANCODE_SPACE) || mouse.button_left_pressed) {

        status = STATUS_PLAYING;
    }
    else if (graphics::getKeyState(graphics::SCANCODE_H)) {

        status = STATUS_HELP;
    }
}

void Level_2::updateHelpScreen() {
    graphics::MouseState mouse;
    graphics::getMouseState(mouse);

    if (graphics::getKeyState(graphics::SCANCODE_T) || mouse.button_left_pressed) {

        status = STATUS_START;
    }
    else {
        status = STATUS_HELP;
    }
}


void Level_2::updateLevelScreen(float dt) {

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
        if (m_game_over_timer > 2000.0f) { // Wait for 2 seconds (2000ms)
            graphics::stopMessageLoop();
        }
        return;
    }


    // Update player_2
    if (m_state->get_Player_2() && m_state->get_Player_2()->isActive()) {
        m_state->get_Player_2()->update(dt);
    }

    // Update pipes
    for (auto& pipe : m_blocks) {
        pipe.update(dt);
    }

    // Update coins
    for (auto& coin : m_coins) {
        coin.update(dt);
    }

    for (auto& extras : m_extras) {
        extras.update(dt);
    }


    //// Update coins_score
    //for (auto& coins_score : m_coin_score) {
    //    coins_score.update(dt);
    //}

    checkCollisions();

    GameObject::update(dt);
}



void Level_2::draw() {

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


void Level_2::drawStartScreen() {
    graphics::Brush br;

    float w = m_state->getCanvasDimensions().first;
    float h = m_state->getCanvasDimensions().second;

    float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
    float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

    br.outline_opacity = 0.0f;
    br.texture = m_state->getFullAssetPath("loading_lvl2.png");
    // Draw background
    graphics::drawRect(offset_x, offset_y, w, h, br);
}

void Level_2::drawHelpScreen() {
    graphics::Brush br;

    float w = m_state->getCanvasDimensions().first;
    float h = m_state->getCanvasDimensions().second;

    float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
    float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

    br.outline_opacity = 0.0f;
    br.texture = m_state->getFullAssetPath("settings_lvl_2.png");
    // Draw background
    graphics::drawRect(offset_x, offset_y, w, h, br);
}

void Level_2::drawLevelScreen() {
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
        if (m_state->get_Player_2()->isActive()) {
            m_state->get_Player_2()->draw();
        }

        // Draw pipes
        for (auto& pipe : m_blocks) {
            pipe.draw();
        }

        // Draw coins
        for (auto& coin : m_coins) {
            coin.draw();
        }

        // Draw extras
        for (auto& extras : m_extras) {
            extras.draw();
        }

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
        // If the game is over, draw the ending background
        //m_brush_background.outline_opacity = 0.0f;
        graphics::drawRect(offset_x, offset_y, ending_bg_width, ending_bg_height, m_brush_ending_background);
    }
}


void Level_2::loseLife() {
    if (m_lives > 0) {
        m_lives--;

        // Remove a heart visually by popping the last heart from the list
        m_hearts.pop_back();

        if (m_lives == 0) {
            m_game_over = true;
        }
    }
}

void Level_2::loseCoin() {
    if (m_coins_for_score > 0) {
        m_coins_for_score--;

        // Remove a coin visually by popping the last coin from the list
        m_coin_score.pop_back();

        /*if (m_coins_for_score == 0) {
            m_game_over = true;
        }*/
    }
}



void Level_2::resetLevel() {
    // Reset player_2 and other objects (existing code)

    Player_Level_2* player = m_state->get_Player_2();
    player->reset();

    // Reset pipes
    for (auto& pipe : m_blocks) {
        pipe.reset();
    }

    // Reset coins
    m_coins.clear();
    m_coins.emplace_back(21.0f, 2.5f, 0.5f, 0.5f, 3.0f, "coin.png");
    m_coins.emplace_back(32.0f, 3.2f, 0.5f, 0.5f, 3.0f, "coin.png");
    m_coins.emplace_back(62.0f, 3.2f, 0.5f, 0.5f, 3.0f, "coin.png");

    for (auto& coin : m_coins) {
        coin.init();
    }


    for (auto& extras : m_extras) {
        extras.reset();
    }

    // Reset hearts' position at the top-left corner
    m_hearts.clear(); // Clears but doesn’t free memory

    float heart_pos_x = 0.3f;  // Positioned near the left edge of the canvas
    float heart_pos_y = 0.3f;  // Positioned near the top edge of the canvas
    float heart_spacing = 0.05f; // Space between hearts

    for (int i = 0; i < m_lives; ++i) {
        m_hearts.emplace_back(heart_pos_x + i * (0.3f + heart_spacing), heart_pos_y, 0.3f, 0.3f, "heart_2.png"); // Example size of 0.3x0.3
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
        m_coin_score.emplace_back(coin_score_pos_x + i * (0.3f + coin_score_spacing), coin_score_pos_y, 0.3f, 0.3f, "coin.png"); // Example size of 0.3x0.3
    }

    for (auto& coin_score : m_coin_score) {
        coin_score.init();
    }

    m_game_paused = false;
}


void Level_2::checkCollisions() {
    if (m_game_paused || m_game_over) return;

    Player_Level_2* player = m_state->get_Player_2();
    if (!player) {
        std::cerr << "Player not initialized!" << std::endl;
        return;
    }

    bool isGrounded = false;  // To track if the player is on a pipe
    bool hasSideCollision = false;  // To track if there's a horizontal collision
    
    // Check block collisions
    for (auto& block : m_blocks) {
        float offset = 0.0f;

        // Check for vertical collision (standing on top of a block)
        if ((offset = player->intersectDown(block)) != 0.0f) {
            player->m_pos_y += offset;  // Adjust player's vertical position
            player->set_velocity_y(0.0f);  // Stop vertical movement
            isGrounded = true;  // Player is on top of a block
        }

        // Check for horizontal collision only if the player is not grounded
        if ((offset = player->intersectSideways(block)) != 0.0f) {
            player->m_pos_x -= offset;  // Adjust player's horizontal position
            player->dead_player_change_photo();
            hasSideCollision = true;  // Flag that a horizontal collision occurred
        }

        // If there's a horizontal collision, we lose a life and pause the game
        if (hasSideCollision) {
            loseLife();
            m_game_paused = true;
            return;
        }
    }

    // Check coin collection
    auto it = m_coins.begin();
    while (it != m_coins.end()) {
        if (player->intersect(*it)) {  // Player collects a coin
            graphics::playSound(m_state->getFullAssetPath("coin.wav"), 0.5f);
            loseCoin();  // Decrease the coin count
            it = m_coins.erase(it);  // Remove the collected coin
        }
        else {
            ++it;  // Move to the next coin
        }
    }

    //// Check extra item collisions
    //for (auto& extra : m_extras) {
    //    if (player->intersect(extra)) {  // Player collides with an extra item
    //        graphics::playSound(m_state->getFullAssetPath("hit.wav"), 0.5f);
    //        loseLife();
    //        m_game_paused = true;
    //        return;
    //    }
    //}
    
    // Check extras collisions
    auto itt = m_extras.begin();
    while (itt != m_extras.end()) {
        if (player->intersect(*itt)) {
            if (itt->getTexture() == "portal.png") {
                graphics::playSound(m_state->getFullAssetPath("lets_go.wav"), 0.5f);
                //m_game_over = true; // End the game when the portal is hit
                m_state->handleGameOver();  // Handle the transition or close the game
                cout << "eftasa";
                return;
            }
            else {
                graphics::playSound(m_state->getFullAssetPath("hit.wav"), 0.5f);
                player->dead_player_change_photo();
                loseLife();
                m_game_paused = true;
                return;
            }
        }
        else {
            ++itt;
        }
    }

    // Check if the player hits the ground
    float floorY = m_state->getCanvasDimensions().second - 0.1f;
    if (player->m_pos_y > floorY) {
        player->m_pos_y = floorY;  // Adjust the player's position to be on the ground
        player->set_velocity_y(0.0f);  // Reset the vertical velocity
        graphics::playSound(m_state->getFullAssetPath("hit.wav"), 0.5f);
        loseLife();
        m_game_paused = true;
    }
}


