#pragma once

#include <iostream>
#include "GameObject.h"
#include "Box.h"
#include <sgg/graphics.h>
#include <string>

class Enemy : public GameObject, public Box {
private:
    graphics::Brush m_enemy_brush;
    graphics::Brush m_enemy_brush_debug;
    std::string m_texture;
    const float m_enemy_speed = 3.0f;

public:  

    bool m_is_alive;  // Add this flag to track if the enemy is alive

    Enemy() : m_is_alive(true) {}


    bool isAlive() const {
        return m_is_alive;
    }

    // Constructor
    Enemy(float pos_x, float pos_y, float width, float height, const std::string& texture);

    // Delete copy constructor and copy assignment operator
    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;

    // Implement move constructor and move assignment operator
    Enemy(Enemy&& other) noexcept;
    Enemy& operator=(Enemy&& other) noexcept;

    void update(float dt) override;
    void init() override;
    void draw() override;
    void setTexture(const std::string& texture);
    std::string getTexture();
    void move(float dt);
};
