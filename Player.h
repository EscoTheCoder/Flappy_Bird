#pragma once

#include "GameObject.h"
#include "box.h"
#include <sgg/graphics.h>
#include <vector>
#include <cmath>

class Player : public GameObject, public Box {
private:
    // Rendering brushes
    graphics::Brush m_brush_player;
    graphics::Brush m_brush_player_debug;

    //vector<string> m_sprites;

    float m_initial_pos_x;
    float m_initial_pos_y;

    // Movement and physics variables
    const float m_gravity = 10.0f;        // Gravity strength
    const float m_jump_force = 2.0f;      // Jump force
    float m_velocity_y = 0.0f;            // Vertical velocity

    void movePlayer(float dt);

public:
    Player(const std::string& name);

    bool isJumping() const;
    float getVelocityY() const;
    bool isFalling() const;

    void reset();

    // Accessor methods
    float getPosX() const;
    float getPosY() const;
    float getWidth() const;
    float getHeight() const;

    void set_velocity_y(float velocity_y) {
        m_velocity_y = velocity_y;
    }

    float get_velocity_y() {
        return m_velocity_y;
    }

    bool is_dead = false;


    void update(float dt) override;
    void init() override;
    void draw() override;

    void dead_player_change_photo();

protected:
    void debugDraw();
};
