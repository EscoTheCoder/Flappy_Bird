#pragma once

#include "GameObject.h"
#include "Box.h"
#include "Laser.h"
#include <sgg/graphics.h>
#include <vector>
#include <memory>  // Include for std::unique_ptr
#include <cmath>
#include <iostream> // For debugging

class Player_Level_3 : public GameObject, public Box {
private:
    // Rendering brushes
    graphics::Brush m_brush_player;
    graphics::Brush m_brush_player_debug;

    float m_initial_pos_x;
    float m_initial_pos_y;

    // Movement and physics variables
    const float m_gravity = 10.0f;        // Gravity strength
    const float m_jump_force = 2.0f;      // Jump force
    float m_velocity_y = 0.0f;            // Vertical velocity
    bool m_isJumping = false;             // Flag for checking if the player is jumping

    std::vector<Laser> m_lasers;  // Use unique_ptr for lasers
    float m_shoot_cooldown = 0.0f;       // Time between consecutive shots
    const float m_laser_cooldown_time = 0.5f; // 0.5 second cooldown for shooting lasers

    void movePlayer(float dt);  // Handle player movement

public:
    Player_Level_3(const std::string& name);

    // Movement methods
    float getVelocityY() const;
    void setVelocityY(float velocity_y);
    float getVelocityY();

    std::vector<Laser> getLasers() {
        return m_lasers;
    }

    // Reset player state
    void reset();

    // Accessor methods
    float getPosX() const;
    float getPosY() const;
    float getWidth() const;
    float getHeight() const;

    // Game loop methods
    void update(float dt) override;   // Update player and laser states
    void init() override;             // Initialize player state
    void draw() override;             // Draw player and lasers

    void shoot();  // Method for shooting a laser
    void dead_player_change_photo();


protected:
    void debugDraw();  // Debug drawing
};