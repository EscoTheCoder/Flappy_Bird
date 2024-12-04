#pragma once

#include <iostream>
#include "GameObject.h"
#include "Box.h"
#include <sgg/graphics.h>
#include <string>

class Laser : public GameObject, public Box {
private:
    graphics::Brush m_laser_brush;
    graphics::Brush m_laser_brush_debug;

    std::string m_texture;
    const float m_laser_speed = 7.0f;  // Speed at which the laser moves (higher value for faster movement)

    float m_initial_pos_x;
    float m_initial_pos_y;

    bool m_is_active;  // Whether the laser is currently active
    float m_speed;     // The speed at which the laser moves



public:
    Laser(float pos_x, float pos_y, float width, float height, const std::string& texture);
    Laser() : Laser(0, 0, 0, 0, "") {} // Default constructor with default initialization

    // Move and copy constructors/operators
    Laser(const Laser& other); // Copy constructor
    Laser& operator=(const Laser& other); // Copy assignment operator

    Laser(Laser&& other) noexcept;
    Laser& operator=(Laser&& other) noexcept;

    // Methods
    void update(float dt) override;
    void init() override;
    void draw() override;
    void move(float dt);
    void reset();

    void activate(float x, float y) {
        m_pos_x = x;
        m_pos_y = y;
        m_is_active = true;
    }

    void deactivate() {
        m_is_active = false;
    }

    void setTexture(const std::string& texture);
    std::string getTexture();
};
