#include "Level_3.h"
#include "GameState.h"
#include "Player_Level_3.h"
#include <sgg/graphics.h>
#include <iostream>

using namespace std;

Level_3::Level_3(const string& name) :
    GameObject(name), m_lives(3), Start_Level("Level3") { // Initialize with 3 lives
}

Level_3::~Level_3() {
    // Clear blocks
    m_blocks.clear();

    // Clear enemies
    m_enemies.clear();

    // Clear hearts
    m_hearts.clear();

    // Clear kills
    m_kills.clear();

    // Optionally log destruction for debugging
    std::cout << "Level 3 destroyed: " << std::endl;
}

void Level_3::init() {
    m_lives = 3; // Reset to 3 lives
    m_kills_for_score = 3;
    m_game_over = false; // Reset game-over flag
    m_game_over_timer = 0.0f; // Reset game-over timer

    // Initialize background
    m_brush_background.outline_opacity = 0.0f;
    m_brush_background.texture = m_state->getFullAssetPath("scary_background.png");

    // Initialize ending background
    m_brush_ending_background.outline_opacity = 0.0f;
    m_brush_ending_background.texture = m_state->getFullAssetPath("win_the_game.png");



    // Initialize static and dynamic objects
    /*for (auto p_gob : m_static_objects) {
        if (p_gob) {
            p_gob->init();
        }
    }
    for (auto p_gob : m_dynamic_objects) {
        if (p_gob) {
            p_gob->init();
        }
    }*/


    // Initialize pipes with positions and textures
    for(int i = 0; i<150; i++){
        //m_extras.emplace_back((float)i, 5.50f, 1.0f, 1.0f, "Ground.png");
        m_blocks.emplace_back((float)i, 5.50f, 1.0f, 1.0f, "floor.png");
    }

    m_blocks.emplace_back(50, 2.5f, 2.0f, 15.0f, "finish_line.png");


    for (auto& block : m_blocks) {
        block.init();
    }
    

    std::srand(static_cast<unsigned>(std::time(0)));  // Seed random number generator

    // Initialize enemies (people) walking on the blocks
    for (int i = 0; i < 10; ++i) {
        float block_pos_x = m_blocks[i * 5].m_pos_x; // Every 5th block has a person

        // Pick a random texture from the enemy_textures vector
        int random_index = std::rand() % enemy_textures.size();
        std::string random_texture = enemy_textures[random_index];
        // Create an enemy with a random texture

        /*if (random_index == 4) {
            m_enemies.emplace_back(block_pos_x, 4.1f, 0.8f, 1.8f, random_texture);
        }
        else {
            m_enemies.emplace_back(block_pos_x, 4.1f, 0.8f, 1.8f, random_texture);
        }*/
        m_enemies.emplace_back(block_pos_x, 4.1f, 0.8f, 1.8f, random_texture);
    }

    for (auto& enemy : m_enemies) {
        enemy.init();
    }

    ////m_extras.emplace_back(75.0f, 3.2f, 2.0f, 5.0f, "do_not_stop_image.png");
    //m_extras.emplace_back(75.0f, 2.5f, 2.0f, 2.0f, "portal.png");

    //for (auto& extras : m_extras) {
    //    extras.init();
    //}

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

    m_kills.clear();
    for (int i = 0; i < m_lives; ++i) {
        m_kills.emplace_back(coin_score_pos_x + i * (0.3f + coin_score_spacing), coin_score_pos_y, 0.3f, 0.3f, "kill_counter.png"); // Example size of 0.3x0.3
    }

    for (auto& kills : m_kills) {
        kills.init();
    }
}



void Level_3::update(float dt) {

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

void Level_3::updateStartScreen() {

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

void Level_3::updateHelpScreen() {
    graphics::MouseState mouse;
    graphics::getMouseState(mouse);

    if (graphics::getKeyState(graphics::SCANCODE_T) || mouse.button_left_pressed) {

        status = STATUS_START;
    }
    else {
        status = STATUS_HELP;
    }
}


void Level_3::updateLevelScreen(float dt) {



    if (m_game_paused) {
        graphics::MouseState mouse;
        graphics::getMouseState(mouse);

        if (mouse.button_left_pressed) {
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


    // Update player
    if (m_state->get_Player_3() && m_state->get_Player_3()->isActive()) {
        m_state->get_Player_3()->update(dt);
    }
 

    // Update pipes
    for (auto& block : m_blocks) {
        block.update(dt);
    }

    // Update enemies
    for (auto& enemy : m_enemies) {
        enemy.update(dt);
    }

    //// Update coins
    //for (auto& coin : m_coins) {
    //    coin.update(dt);
    //}

    //for (auto& extras : m_extras) {
    //    extras.update(dt);
    //}


    //// Update coins_score
    //for (auto& coins_score : m_coin_score) {
    //    coins_score.update(dt);
    //}

    checkCollisions();

    GameObject::update(dt);
}



void Level_3::draw() {

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

void Level_3::drawStartScreen() {
    graphics::Brush br;

    float w = m_state->getCanvasDimensions().first;
    float h = m_state->getCanvasDimensions().second;

    float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
    float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

    br.outline_opacity = 0.0f;
    br.texture = m_state->getFullAssetPath("loading_lvl3.png");
    // Draw background
    graphics::drawRect(offset_x, offset_y, w, h, br);
}

void Level_3::drawHelpScreen() {
    graphics::Brush br;

    float w = m_state->getCanvasDimensions().first;
    float h = m_state->getCanvasDimensions().second;

    float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
    float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

    br.outline_opacity = 0.0f;
    br.texture = m_state->getFullAssetPath("settings_lvl_3.png");
    // Draw background
    graphics::drawRect(offset_x, offset_y, w, h, br);
}

void Level_3::drawLevelScreen() {
    float w = m_state->getCanvasDimensions().first;
    float h = m_state->getCanvasDimensions().second;

    float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
    float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

    // Draw background
    graphics::drawRect(offset_x, offset_y, w, h, m_brush_background);

    if (!m_game_over) {
        // Draw blocks
        for (auto& block : m_blocks) {
            block.draw();
        }

        // Draw people walking on the blocks (enemies)
        for (auto& enemy : m_enemies) {
            enemy.draw();
        }

        // Draw hearts (lives) on the left side of the canvas
        for (auto& heart : m_hearts) {
            heart.draw();
        }

        // Draw coin (score) on the left side of the canvas
        for (auto& kills : m_kills) {
            kills.draw();
        }

        // Draw player (bird)
        if (m_state->get_Player_3()->isActive()) {
            m_state->get_Player_3()->draw();
        }
    }
    else {
        // If the game is over, draw the ending background
        graphics::drawRect(offset_x, offset_y, w, h, m_brush_ending_background);
    }
}


void Level_3::loseLife() {
    if (m_lives > 0) {
        m_lives--;
        
        // Remove a heart visually by popping the last heart from the list
        m_hearts.pop_back();
        
        if (m_lives == 0) {
            m_game_over = true;
            graphics::playSound(m_state->getFullAssetPath("game_over.wav"), 0.5f);
        }
    }
}

void Level_3::KillEnemy() {
    if (m_kills_for_score > 0) {
        m_kills_for_score--;

        // Remove a coin visually by popping the last coin from the list
        m_kills.pop_back();

        if (m_kills_for_score == 0) {
            m_game_over = true; // This could trigger the game to stop
            graphics::playSound(m_state->getFullAssetPath("music_1.wav"), 0.5f);
        }
        std::cout << "Enemy killed. Kills left: " << m_kills_for_score << std::endl;
    }
}



void Level_3::resetLevel() {
    // Reset player and other objects (existing code)

    Player_Level_3* player = m_state->get_Player_3();
    player->reset();

    // Reset pipes
    for (auto& block : m_blocks) {
        block.reset();
    }

    m_enemies.clear();
    // Reset enemies (people) walking on the blocks
    for (int i = 0; i < 10; i++) {
        float block_pos_x = m_blocks[i * 5].m_pos_x; // Every 10th block has a person

        int random_index = std::rand() % enemy_textures.size();
        std::string random_texture = enemy_textures[random_index];

        m_enemies.emplace_back(block_pos_x, 4.1f, 0.8f, 1.8f, random_texture); // Set person texture
    }

    for (auto& enemy : m_enemies) {
        enemy.init();
    }

    float heart_pos_x = 0.3f;  // Positioned near the left edge of the canvas
    float heart_pos_y = 0.3f;  // Positioned near the top edge of the canvas
    float heart_spacing = 0.05f; // Space between hearts

    m_hearts.clear();
    for (int i = 0; i < m_lives; i++) {
        m_hearts.emplace_back(heart_pos_x + i * (0.3f + heart_spacing), heart_pos_y, 0.3f, 0.3f, "heart.png"); // Example size of 0.3x0.3
    }

    for (auto& heart : m_hearts) {
        heart.init();
    }

    // Position the coins at the top-left corner
    float coin_score_pos_x = 0.3f;  // Positioned near the left edge of the canvas
    float coin_score_pos_y = 0.7f;  // Positioned near the top edge of the canvas
    float coin_score_spacing = 0.05f; // Space between hearts

    m_kills.clear();
    for (int i = 0; i < m_kills_for_score; i++) {
        m_kills.emplace_back(coin_score_pos_x + i * (0.3f + coin_score_spacing), coin_score_pos_y, 0.3f, 0.3f, "kill_counter.png"); // Example size of 0.3x0.3
    }

    for (auto& kills : m_kills) {
        kills.init();
    }

    m_game_paused = false;
}


void Level_3::checkCollisions() {
    if (m_game_paused || m_game_over) return;

    Player_Level_3* player = m_state->get_Player_3();
    if (!player) {
        std::cerr << "Player not initialized!" << std::endl;
        return;
    }

    // Iterator for enemies list
    auto it = m_enemies.begin();

    // Check player-enemy collisions
    while (it != m_enemies.end()) {
        Enemy& enemy = *it;

        if (enemy.isAlive() && (player->intersectDown(enemy) || player->intersectSideways(enemy))) {
            player->dead_player_change_photo();
            graphics::playSound(m_state->getFullAssetPath("hit.wav"), 0.5f);
            loseLife();
            m_game_paused = true;
            return;
        }

        // Check if lasers hit enemies
        bool enemy_hit = false;
        for (auto& laser : player->getLasers()) {
            if (laser.isActive() && enemy.isAlive() && laser.intersect(enemy)) {
                // Enemy hit logic
                graphics::playSound(m_state->getFullAssetPath("aetos.wav"), 0.5f);
                KillEnemy();           // Handle enemy being hit
                //laser->deactivate();   // Deactivate the laser or remove it
                enemy_hit = true;      // Mark that this enemy was hit
                break;                 // Exit the laser loop since the enemy is already hit
            }
        }

        if (enemy_hit) {
            // If the enemy is hit, remove it from the list and continue
            it = m_enemies.erase(it);  // Erase returns the next iterator
        }
        else {
            ++it;  // Move to the next enemy if no hit occurred
        }
    }



    // Check pipe collisions
    for (auto& block : m_blocks) {
        // First, check for vertical collision (standing on top of a pipe)
        if (player->intersectDown(block) || player->intersectSideways(block)) {
            if (block.getTexture() == "finish_line.png") {
                player->dead_player_change_photo();
                graphics::playSound(m_state->getFullAssetPath("hit.wav"), 0.5f);
                loseLife();
                m_game_paused = true;
                return;
            }
            else {
                graphics::playSound(m_state->getFullAssetPath("hit.wav"), 0.5f);
                loseLife();
                m_game_paused = true;
                return;
            }
        }
    }


    // Check if the player hits the ground
    float floorY = m_state->getCanvasDimensions().second - 0.1f;
    if (player->m_pos_y > floorY) {
        player->m_pos_y = floorY;  // Adjust the player's position to be on the ground
        player->setVelocityY(0.0f);  // Reset the vertical velocity
        graphics::playSound(m_state->getFullAssetPath("hit.wav"), 0.5f);
        loseLife();
        m_game_paused = true;
    }
}


