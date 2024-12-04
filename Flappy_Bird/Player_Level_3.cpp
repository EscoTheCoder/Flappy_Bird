#include "Player_Level_3.h"
#include "Laser.h"
#include "GameState.h"
#include "util.h"

Player_Level_3::Player_Level_3(const std::string& name) :
    GameObject(name), m_shoot_cooldown(0.0f)
{
    m_width = 0.4f;
    m_height = 0.4f;
}

void Player_Level_3::init() {
    // Set the initial position for the player only when the game starts
    m_pos_x = m_state->getCanvasDimensions().first / 4.0f;  // Starting position (left side)
    m_pos_y = m_state->getCanvasDimensions().second / 5.5f;

    // Store the initial position
    m_initial_pos_x = m_pos_x;
    m_initial_pos_y = m_pos_y;

    m_velocity_y = 0.0f; // Reset velocity

    // Set player brush for rendering
    m_brush_player.fill_opacity = 1.0f;
    m_brush_player.outline_opacity = 0.0f;
    m_brush_player.texture = m_state->getFullAssetPath("green_bird_up.png");

    // Debug brush for rendering
    m_brush_player_debug.fill_opacity = 0.1f;
    SETCOLOR(m_brush_player_debug.fill_color, 1.0f, 0.0f, 0.0f);
    SETCOLOR(m_brush_player_debug.outline_color, 0.0f, 0.0f, 1.0f);
}

void Player_Level_3::reset() {
    // Reset player to the initial starting position and velocity
    m_pos_x = m_initial_pos_x;
    m_pos_y = m_initial_pos_y;
    m_velocity_y = 0.0f;
    m_isJumping = false;

    // Clear all lasers
    m_lasers.clear();
    m_shoot_cooldown = 0.0f;
}

float Player_Level_3::getPosX() const { return m_pos_x; }
float Player_Level_3::getPosY() const { return m_pos_y; }
float Player_Level_3::getWidth() const { return m_width; }
float Player_Level_3::getHeight() const { return m_height; }

void Player_Level_3::setVelocityY(float velocity_y) {
    m_velocity_y = velocity_y;
}

float Player_Level_3::getVelocityY() const {
    return m_velocity_y;
}

void Player_Level_3::movePlayer(float dt) {
    float delta_time = dt / 1000.0f;  // Convert milliseconds to seconds

    // Jumping logic based on Space Button

    // Allow jumping only if the player is not already jumping
    if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
        m_velocity_y = -m_jump_force;  // Apply jump force when clicking
        m_isJumping = true;  // Set the jumping flag
    }

    // Apply gravity
    m_velocity_y += m_gravity * delta_time;

    // Update player vertical position
    m_pos_y += m_velocity_y * delta_time;

    // Set the appropriate texture based on the direction of movement
    if (m_velocity_y < 0) {
        m_brush_player.texture = m_state->getFullAssetPath("green_bird_down.png");
    }
    else {
        m_brush_player.texture = m_state->getFullAssetPath("green_bird_up.png");
    }

    // Prevent player from falling off-screen (ground level)
    if (m_pos_y + m_height / 2.0f > m_state->getCanvasDimensions().second) {
        m_pos_y = m_state->getCanvasDimensions().second - m_height / 2.0f;
        m_velocity_y = 0.0f;
        m_isJumping = false;  // Reset jumping state when hitting the ground
    }

    // Prevent player from going above the screen
    if (m_pos_y - m_height / 2.0f < 0) {
        m_pos_y = m_height / 2.0f;
        m_velocity_y = 0.0f;
    }
}

void Player_Level_3::update(float dt) {
    // Update player movement
    movePlayer(dt);

    graphics::MouseState mouse;
    graphics::getMouseState(mouse);

    if (mouse.button_left_pressed) {  // Detect spacebar press
        shoot();
    }

    // Update laser cooldown
    if (m_shoot_cooldown > 0.0f) {
        m_shoot_cooldown -= dt / 1000.0f;  // Decrease cooldown by delta time
    }

    // Update and move all lasers
    for (auto it = m_lasers.begin(); it != m_lasers.end();) {
        (*it).update(dt);  // Update laser movement

        // Remove laser if it's off the screen
        if ((*it).m_pos_y < 0) {
            it = m_lasers.erase(it);  // Remove laser and get next iterator
        }
        else {
            ++it;
        }
    }
}

void Player_Level_3::shoot() {
    if (m_shoot_cooldown <= 0.0f) {
        std::cout << "Shooting laser!" << std::endl;

        // Create and initialize a new laser
        m_lasers.emplace_back(m_pos_x + m_width / 4.0f, m_pos_y, 0.3, 0.3f, "bullett.png");

        for (int i = 0; i < m_lasers.size(); i++) {
            m_lasers[i].init();
            //m_lasers[i].activate(m_pos_x + m_width / 4.0f, m_pos_y);  // Activate and set position
            //cout << m_lasers[i].getTexture();
        }

        m_shoot_cooldown = m_laser_cooldown_time;
    }
}

void Player_Level_3::draw() {
    // Draw player
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_player);

    // Debugging: draw player details
    debugDraw();

    // Draw all lasers
    for (auto& laser : m_lasers) {
        laser.draw();  // Draw each laser
    }
}

void Player_Level_3::dead_player_change_photo() {
    if (m_brush_player.texture == m_state->getFullAssetPath("green_bird_up.png")) {
        m_brush_player.texture = m_state->getFullAssetPath("green_bird_dead.png");
    }
    else {
        m_brush_player.texture = m_state->getFullAssetPath("green_bird_up.png");
    }
}

void Player_Level_3::debugDraw() {
    if (m_state->m_debugging) {
        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_player_debug);

        // Draw player position coordinates
        char s[20];
        sprintf_s(s, "(%5.2f, %5.2f)", m_pos_x, m_pos_y);
        graphics::drawText(m_pos_x - 0.4f, m_pos_y - 0.6f, 0.15f, s, m_brush_player_debug);
    }
}
