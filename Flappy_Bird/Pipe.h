#pragma once

#include <iostream>
#include "GameObject.h"
#include "box.h"
#include <sgg/graphics.h>
#include <string>

class Pipe : public GameObject, public Box {
private:
    graphics::Brush m_pipe_brush;         // Brush for drawing the pipe
    graphics::Brush m_pipe_brush_debug;   // Brush for drawing the debug outline

    string m_texture;                // Texture file for the pipe
    const float m_pipe_speed = 5.0f;      // Speed at which the pipe moves left

    const float m_oscillation_amplitude = 0.5f; // How much the pipe moves up and down
    const float m_oscillation_speed = 1.0f;      // Speed of the up-and-down movement
    float m_time_passed = 0.0f;                 // Time passed for calculating sine wave

    float m_initial_pos_x;
    float m_initial_pos_y; 

public:
    Pipe(float pos_x, float pos_y, float width, float height, const string& texture);

    void update(float dt) override;
    void init() override;
    void draw() override;

    void setTexture(const std::string& texture);
    void move(float dt);                  // Method to move the pipe

    void reset();
};
