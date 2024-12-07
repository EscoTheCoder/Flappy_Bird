#include "Pipe.h"
#include "GameState.h"
#include "util.h"
#include <sgg/graphics.h>
#include <cmath>  // For the sin() function

Pipe::Pipe(float pos_x, float pos_y, float width, float height, const std::string& texture) :
    GameObject("Pipe"), Box(pos_x, pos_y, width, height), m_texture(texture)
{
}

void Pipe::init() {
    m_pipe_brush.outline_opacity = 0.0f; // No outline for the pipe
    m_pipe_brush.texture = m_state->getFullAssetPath(m_texture); // Set the texture

    m_pipe_brush_debug.fill_opacity = 0.1f; // Lightly transparent debug fill
    SETCOLOR(m_pipe_brush_debug.fill_color, 1.0f, 0.0f, 0.0f); // Red color for the debug outline
    SETCOLOR(m_pipe_brush_debug.outline_color, 0.0f, 1.0f, 0.0f); // Green outline color for debugging

    // ������������ ��� ������ ���� ���� ��� ������������
    m_initial_pos_x = m_pos_x;
    m_initial_pos_y = m_pos_y;
}

void Pipe::update(float dt) {
    move(dt); // Move the pipe according to the game logic
}

void Pipe::draw() {
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_pipe_brush);

    if (m_state->m_debugging) {
        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_pipe_brush_debug);
    }
}

void Pipe::reset() {
    // ��������� ��� ����� ��� ������ ���� ������ ���������
    m_pos_x = m_initial_pos_x;
    m_pos_y = m_initial_pos_y;
}

void Pipe::move(float dt) {
    // Update the horizontal position (move left)
    m_pos_x -= m_pipe_speed * (dt / 1000.0f);

    // Update the vertical position (move up and down in a sine wave pattern)
    m_time_passed += dt / 1000.0f; // Convert dt to seconds
    m_pos_y = m_initial_pos_y + m_oscillation_amplitude * sin(m_oscillation_speed * m_time_passed);
}

void Pipe::setTexture(const std::string& texture) {
    m_texture = texture; 
    m_pipe_brush.texture = m_state->getFullAssetPath(m_texture); // Update the brush texture
}
